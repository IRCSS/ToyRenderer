@echo off
cd /D "%~dp0"
set /p ProjName="Enter the name of your project: "

if not exist %ProjName%\\src MkDir %ProjName%\\src
copy "ToyRendererStarterContent\\SandBoxApp.cpp" "%ProjName%\\src\\SandBoxApp.cpp" /b/v/y

if not exist %ProjName%\\res MkDir %ProjName%\\res

xcopy /Q /E /Y /I "ToyRendererStarterContent\\res" "%ProjName%\\res"

call premake\premake5.exe vs2017 --GameName="%ProjName%"
PAUSE