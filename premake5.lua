workspace "CarData"
	architecture "x64"
	startproject "CarData"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "CarData/vendor/GLFW/include"
IncludeDir["Glad"] = "CarData/vendor/Glad/include"
--IncludeDir["ImGui"] = "CarData/vendor/imgui"

include "CarData/vendor/GLFW"
include "CarData/vendor/Glad"
--include "CarData/vendor/imgui"

project "CarData"
	location "CarData"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cdpch.h"
	pchsource "CarData/src/cdpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.txt"
	}

	includedirs
	{
		"%{prj.name}/src",
		"D:/Python3.9.7/include",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		--"%{IncludeDir.ImGui}"
	}

	libdirs
	{
		"D:/Python3.9.7/libs"
	}

	links
	{
		"python39.lib",
		"GLFW",
		"opengl32.lib",
		"Glad",
		--"ImGui"
	}

	filter "system:windows"
            	systemversion "latest"
            	staticruntime "On"

		defines
		{
			"CD_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"