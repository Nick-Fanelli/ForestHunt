workspace "ForestHunt"
    architecture "x86_64"
    startproject "ForestHunt"

    flags {
        "MultiProcessorCompile"
    }

    configurations {
        "Debug",
        "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ForestHunt"

kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ( "%{wks.location}/build/" .. outputdir .. "/%{prj.name}")
    objdir ( "%{wks.location}/build-int/" .. outputdir .. "/%{prj.name}")

    pchheader "src/pch.h"

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "src",

        "vendor",
        "vendor/glfw/include",
    }

    links {
        "GLFW",
        "Glad"
    }

    filter "system:macosx"
        links {
            "Cocoa.framework",
            "OpenGL.framework",
            "IOKit.framework",
            "CoreVideo.framework"
        }

    filter "system:linux"
        links {
            "dl",
            "pthread"
        }

        defines {
            "_X11"
        }

    filter "system:windows"
        defines {
            "_WINDOWS"
        }

    filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

        defines {
            "DEBUG"
        }

	filter "configurations:Release"
		runtime "Release"
        optimize "On"

        defines {
            "NDEBUG"
        }

include "vendor/glfw/premake5.lua"
include "vendor/glad/premake5.lua"