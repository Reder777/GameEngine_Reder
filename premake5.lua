workspace "Reder"
    configurations{
        "Debug",
        "Release"
    }

    architecture "x64"

outputdir= "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


--[[
     ----------------------------project Reder------------------------------------
--]]
project "Reder"
    location "Reder"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    includedirs{
        "%{prj.name}/modules/spdlog/include"
    }
    filter "system:Windows"
        system("windows")
        cppdialect "C++14"
        staticruntime "On"
        systemversion "10.0"
        defines{
            "RE_PLATFORM_WINDOWS",
            "RE_DLL_BUILD"
        }

        postbuildcommands{
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox")
        }
    filter "configurations:Debug"
        defines {"RE_DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"RE_RELEASE"}
        optimize "On"

--[[
     ----------------------------project Sandbox------------------------------------
--]]

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files{
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    includedirs{
        "Reder/modules/spdlog/include",
        "Reder/src"
    }
    links{
        "Reder"
    }
    filter "system:Windows"
        system("windows")
        cppdialect "C++14"
        staticruntime "On"
        systemversion "10.0"
        defines{
            "RE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines {"RE_DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"RE_RELEASE"}
        optimize "On"