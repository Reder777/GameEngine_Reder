workspace "Reder"
    configurations{
        "Debug",
        "Release"
    }

    architecture "x64"

outputdir= "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

startproject="Sandbox"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Reder/modules/glfw/include"
IncludeDir["GLAD"] = "Reder/modules/glad/include"
IncludeDir["IMGUI"] = "Reder/modules/imgui"
IncludeDir["GLM"] ="Reder/modules/glm"


include "Reder/modules/glfw"
include "Reder/modules/glad"
include "Reder/modules/imgui"



--[[
     ----------------------------project Reder--------------------------------------
     -------------------------------------------------------------------------------
--]]
project "Reder"
    location "Reder"
    kind "StaticLib"
    language "C++"
    staticruntime "on"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp", 
        "%{prj.name}/modules/glm/glm/**.hpp",
        "%{prj.name}/modules/glm/glm/**.inl"
    }
    pchheader "repch.h"
    pchsource "Reder/src/repch.cpp"
    includedirs{
        "%{prj.name}/src",
        "%{prj.name}/modules/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.IMGUI}",
        "%{IncludeDir.GLM}"
    }
    links{
        "GLFW",
        "opengl32.lib",
        "GLAD",
        "ImGui"
    }
    filter "system:Windows"
        system("windows")
        cppdialect "C++14"
        systemversion "10.0"
        defines{
            "RE_PLATFORM_WINDOWS",
            "RE_DLL_BUILD",
            "GLFW_INCLUDE_NONE",
            "IMGUI_API=__declspec(dllexport)"
        }

    filter "configurations:Debug"
        defines {"RE_DEBUG"}
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines {"RE_RELEASE"}
        runtime "Release"
        optimize "on"

--[[
     ----------------------------project Sandbox------------------------------------
     -------------------------------------------------------------------------------
--]]

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++14"
    staticruntime "on"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    includedirs{
        "Reder/modules/spdlog/include",
        "Reder/src",
        "Reder/modules/imgui",
        "%{IncludeDir.GLM}"
    }
    links{
        "Reder"
    }
    filter "system:Windows"
        system("windows")
        systemversion "10.0"
        defines{
            "RE_PLATFORM_WINDOWS",
            "IMGUI_API=__declspec(dllimport)"
        }

    filter "configurations:Debug"
        defines {"RE_DEBUG"}
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines {"RE_RELEASE"}
        runtime "Release"
        optimize "on"