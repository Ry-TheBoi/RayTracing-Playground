include "Dependencies.lua"

--Project Workspace Configs
workspace "RayTracing-Playgruond"
configurations { "Debug", "Release", "Dist" }
	targetdir "build"
	startproject "RayTracing-Playgruond"

	configurations 
	{ 
		"Debug", 
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	filter "language:C++ or language:C"
		architecture "x86_64"
	filter ""
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Dependencies.lua"

--External Dependencis Folder
group "Dependencies"
include "RayTracing-Playgruond/3rdParty/ImGui"
include "RayTracing-Playgruond/3rdParty/GLFW"
group ""


--Application Config
project "RayTracing-Playgruond"
	location "RayTracing-Playgruond"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	
	files 
	{ 
		"%{prj.name}/Source/**.h", 
		"%{prj.name}/Source/**.c", 
		"%{prj.name}/Source/**.hpp", 
		"%{prj.name}/Source/**.cpp" 
	}
	
	includedirs 
	{
		"%{prj.name}/3rdParty/glfw/include",
		"%{prj.name}/3rdParty/stb_image",
		"%{prj.name}/Source",
		"%{prj.name}/Resources",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.VulkanSDK}",
	}

	links
	{
		"ImGui",
		"GLFW",

		"%{Library.Vulkan}",
	}
	
	filter "system:windows"
		systemversion "latest"
				
		defines 
		{ 
			"RYAPP_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		symbols "On"
		runtime "Debug"

		defines 
		{
			"RYAPP_DEBUG",
			"RYAPP_TRACK_MEMORY"
		}
				
	filter "configurations:Release"
		defines
		{
			"RYAPP_RELEASE",
			"RYAPP_TRACK_MEMORY"
		}

		runtime "Release"
		symbols "On"
		optimize "On"

	filter "configurations:Dist"
		kind "WindowedApp" --Excludes debug console for distribution builds
		defines "RYAPP_DIST"
		runtime "Release"
		optimize "On"
		symbols "Off"
