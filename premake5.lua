-- OpenGL-Sandbox
workspace "OpenGL-Sandbox"
	architecture "x64"
	startproject "OpenGL-Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"




project "GLFW"
	kind "StaticLib"
	language "C"
	location "vendor/GLFW"
	files
	{
		"vendor/GLFW/include/GLFW/glfw3.h",
		"vendor/GLFW/include/GLFW/glfw3native.h",
		"vendor/GLFW/src/glfw_config.h",
		"vendor/GLFW/src/context.c",
		"vendor/GLFW/src/init.c",
		"vendor/GLFW/src/input.c",
		"vendor/GLFW/src/monitor.c",
		"vendor/GLFW/src/vulkan.c",
		"vendor/GLFW/src/window.c"
	}
	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"vendor/GLFW/src/win32_init.c",
			"vendor/GLFW/src/win32_joystick.c",
			"vendor/GLFW/src/win32_monitor.c",
			"vendor/GLFW/src/win32_time.c",
			"vendor/GLFW/src/win32_thread.c",
			"vendor/GLFW/src/win32_window.c",
			"vendor/GLFW/src/wgl_context.c",
			"vendor/GLFW/src/egl_context.c",
			"vendor/GLFW/src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
	
	
	includedirs{
		"vendor/GLFW/include"
	}
	targetdir ("./bin/" .. outputdir .. "/%{prj.name}")
	objdir ("./bin-int/" .. outputdir .. "/%{prj.name}")

project "ImGui"
	kind "StaticLib"
	language "C++"
	location "vendor/imgui"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"vendor/imgui/**.h",
		"vendor/imgui/**.cpp",
	}
	includedirs
	{

		"vendor/GLFW/include",
		"vendor/Glad/include",
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
	links {
		"GLFW"
	}

project "Glad"
	kind "StaticLib"
	language "C"
	location "vendor/Glad"
	files
	{
		"vendor/Glad/**.h",
		"vendor/Glad/**.cpp",
		"vendor/Glad/**.c"
	}
	includedirs{
		"vendor/Glad/include"
	}
	targetdir ("./bin/" .. outputdir .. "/%{prj.name}")
	objdir ("./bin-int/" .. outputdir .. "/%{prj.name}")


project "OpenGL-Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("./bin/" .. outputdir .. "/%{prj.name}")
	objdir ("./bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.c",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/**.hpp",
		"vendor/glm/**.inl",
	}

	includedirs
	{
		"src",
		"vendor",
		"vendor/GLFW/include",
		"vendor/Glad/include",
		"vendor/imgui",
		"vendor/glm",
		"vendor/stb_image"
	}
	
	
	links {
		"Glad",
		"GLFW",
		"ImGui"
	}
	

