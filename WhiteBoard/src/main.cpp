#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#define POOL_MAX 50

class ThreadPool
{
public:
	ThreadPool()
	{
		Workers.reserve(POOL_MAX);
		for (uint32_t i = 0; i < POOL_MAX; ++i)
		{
			Workers.emplace_back([this]() {this->Woker();});
		}
	}
	~ThreadPool()
	{
		Stop = true;
		cv.notify_all();
		for (auto& worker : Workers)
		{
			worker.join();
		}
	}

	template<typename Func, typename... Args>
	decltype(auto) EnqueueJob(Func&& function, Args&&... args)
	{
		using ReturnType = std::result_of_t<Func(Args...)>;
		using ThisReturnType = std::future<ReturnType>;

		auto job = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<Func>(function), std::forward<Args>(args)...));

		ThisReturnType ret = job->get_future();
		{
			std::lock_guard<std::mutex> lock(mtx);
			Jobs.push([job]() { (*job)(); });
		}
		cv.notify_one();
		return ret;
	}

	void Woker()
	{
		while (1)
		{
			std::unique_lock<std::mutex> lock(mtx);
			cv.wait(lock, [this]() {
				return !Jobs.empty() || Stop;
			});

			if (Stop) break;

			auto job = Jobs.front();
			Jobs.pop();
			lock.unlock();

			job();
		}
	}

	std::queue<std::function<void()>> Jobs;
	std::vector<std::thread> Workers;
	std::condition_variable cv;
	bool Stop = false;
	std::mutex mtx;
};

// ��� ����
int work(int t, int id) 
{
	printf("%d start \n", id);
	std::this_thread::sleep_for(std::chrono::seconds(t));
	printf("%d end after %ds\n", id, t);
	return t + id;
}

void some()
{
	printf("hellow");
}

int main() {
	ThreadPool pool;

	std::vector<std::future<int>> futures;
	for (int i = 0; i < 10; i++) 
	{
		futures.emplace_back(pool.EnqueueJob(work, i % 3 + 1, i));
	}
	
	
}