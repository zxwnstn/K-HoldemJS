workspace "K-Holdem"
	configurations
	{
		"Debug",
		"Release"
	}

	platforms
	{
		"x64"
	}
	
	characterset ("Unicode")

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "vendor/googletest"

project "entt"
	location "vendor/entt"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"vendor/entt/src/**.h",
		"vendor/entt/src/**.hpp",
		"vendor/entt/src/**.cpp"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	
	filter "configurations:Release"
		optimize "On"


project "HoldemCore"
	location "HoldemCore"
	kind "StaticLib"
	language "C++"
	
	--pchheader "pch.h"
	--pchsource "src/pch.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"vendor/entt/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "On"


project "HoldemApp"
	location "HoldemApp"
	kind "ConsoleApp"
	language "C++"
	
	--pchheader "pch.h"
	--pchsource "src/pch.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"HoldemCore/src",
		"vendor/entt/src"
	}
	links
	{
		"HoldemCore"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	
	filter "configurations:Release"
		optimize "On"

project "Test"
	location "Test"
	kind "ConsoleApp"
	language "C++"
	
	pchheader "pch.h"
	pchsource "pch.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}
	includedirs
	{
		"%{prj.name}",
		"HoldemCore/src",
		"HoldemApp/src",
		"vendor/googletest/googletest/include",
		"vendor/entt/src"
	}
		
	links
	{
		"gtest",
		"HoldemCore",
		"HoldemApp"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	
	filter "configurations:Release"
		optimize "On"

project "WhiteBoard"
	location "WhiteBoard"
	kind "ConsoleApp"
	language "C++"
	
	--pchheader "pch.h"
	--pchsource "src/pch.cpp"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	includedirs
	{
		"%{prj.name}/src",
		"vendor/entt/src",
		"vendor/googletest/googletest/include"
	}
	links
	{
		"gtest"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		symbols "On"
	
	filter "configurations:Release"
		optimize "On"

