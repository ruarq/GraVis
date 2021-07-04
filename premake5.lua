workspace "Gravity-Visualisation"
	configurations { "Debug", "Release" }

project "Gravity-Visualisation"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir "Bin/%{cfg.buildcfg}"
	objdir "Obj"

	includedirs { "Source" }

	files { "Source/**.hpp", "Source/**.cpp" }
	links { "sfml-system", "sfml-window", "sfml-graphics" }

	filter { "configurations:Debug" }
		symbols "On"
		defines { "DEBUG" }

	filter { "configurations:Release" }
		optimize "On"