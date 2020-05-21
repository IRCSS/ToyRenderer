newoption {
  trigger     = "GameName",
  value       = "NameOfTheGame",
  description = "Give Your project a name",
  default     = "ExampleGame",
}

if not _OPTIONS["GameName"] then
  _OPTIONS["GameName"] = "ExampleGame"
end
workspace (_OPTIONS["GameName"])
architecture "x64"
configurations {
    "Debug",
    "Release",
    "Shipping"
 }
 outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

 project (_OPTIONS["GameName"])
 location (_OPTIONS["GameName"])
 kind "ConsoleApp"
 language "C++"

 targetdir("binaries/" ..outputdir.. "/%{prj.name}")
 objdir("intermediates/" ..outputdir.. "/%{prj.name}")

 files{
     "%{prj.name}/src/**.h",
     "%{prj.name}/src/**.cpp",
  }

  libdirs { 
    "ToyRendererDistrubtionFiles",
 }

  includedirs{
    "ToyRendererDistrubtionFiles/include"
  }

  links{
      "ToyRenderer.lib"
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

   postbuildcommands{
    ("copy ..\\ToyRendererDistrubtionFiles\\ToyRenderer.dll ..\\binaries\\" ..outputdir.. "\\%{prj.name}\\ /y"),
    ("xcopy ..\\ToyRendererDistrubtionFiles\\res ..\\binaries\\" ..outputdir.. "\\%{prj.name}\\res\\ /s /e /y")
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