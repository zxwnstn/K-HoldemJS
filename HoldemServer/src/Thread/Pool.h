#pragma once

#include <condition_variable>
#include <future>
#include <queue>
#include <mutex>

#define POOL_MAX 50

class ThreadPool
{
public:
	ThreadPool()
	{
		Workers.reserve(POOL_MAX);
		for (uint32_t i = 0; i < POOL_MAX; ++i)
		{
			Workers.emplace_back([this]() {this->Woker(); });
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