workspace "ToyRenderer"
	architecture "x64"

	configurations {
       "Debug",
	   "Release",
	   "Shipping"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	project "ToyRenderer"
		location "ToyRenderer"
		kind "SharedLib"
		language "C++"

		targetdir("ToyRenderer-binaries/" ..outputdir.. "/%{prj.name}")
		objdir("ToyRenderer-intermediates/" ..outputdir.. "/%{prj.name}")

		files{
		  "%{prj.name}/src/**.h",
		  "%{prj.name}/src/**.cpp",
		  "%{prj.name}/src/**.hpp",
		  "%{prj.name}/src/**.inl",
		  "%{prj.name}/dependencies/**.h",
		  "%{prj.name}/ToyRenderer.h"
		}

		includedirs{
			"%{prj.name}/src",
			"%{prj.name}/src/vendor",
			"%{prj.name}/dependencies/GLFW/include",
			"%{prj.name}/dependencies/GLEW/include"
		}

		libdirs { 
			"%{prj.name}/dependencies/GLFW/lib-vc2017",
			"%{prj.name}/dependencies/GLEW/lib/Release/x64"
		 }
		links{
			"glfw3.lib", "glew32s.lib", "opengl32.lib"
		}

		filter {"system:windows"}
			cppdialect "C++17"
			staticruntime "on"
			systemversion "latest"

		defines{
			"TOYRENDERER_PLATFORM_WINDOWS",
			"TOYRENDERER_BUILD_DLL",
			"_MBCS",
			"GLEW_STATIC"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../ToyRenderer-binaries/" ..outputdir.. "/SandBox")
		}

		filter "configurations:Debug"
			defines {"TOYRENDERER_DEBUG"}
			symbols "On"
		
		filter "configurations:Release"
			defines {"TOYRENDERER_RELEASE"}
			optimize "On"

		filter "configurations:Shipping"
			defines {"TOYRENDERER_SHIPPING"}
			optimize "On"

project "Sandbox"
        location "example/Sandbox"
        kind "ConsoleApp"
		language "C++"

		targetdir("ToyRenderer-binaries/" ..outputdir.. "/%{prj.name}")
		objdir("ToyRenderer-intermediates/" ..outputdir.. "/%{prj.name}")

		files{
		  "example/%{prj.name}/src/**.h",
		  "example/%{prj.name}/src/**.cpp",
		}

		includedirs{
	     	"ToyRenderer"
		}

		links{
	    	"ToyRenderer"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

		defines{
			"TOYRENDERER_PLATFORM_WINDOWS",
			"_MBCS",
			"GLEW_STATIC"
		}

		filter "configurations:Debug"
			defines "TOYRENDERER_DEBUG"
			symbols "On"
		
		filter "configurations:Release"
			defines "TOYRENDERER_RELEASE"
			optimize "On"

		filter "configurations:Shipping"
			defines "TOYRENDERER_SHIPPING"
			optimize "On"