workspace "Gravity-Visualization"
	configurations { "debug", "release" }

project "Gravity-Visualization"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir "bin/%{cfg.buildcfg}"
	objdir "obj"

	files { "source/**.hpp", "source/**.cpp" }

	includedirs { "source" }
	links { "sfml-system", "sfml-window", "sfml-graphics" }

	filter { "configurations:debug" }
		symbols "On"

	filter { "configurations:release" }
		optimize "On"