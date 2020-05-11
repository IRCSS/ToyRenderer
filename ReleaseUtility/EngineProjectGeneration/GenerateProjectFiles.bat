@echo off
cd /D "%~dp0"
set /p ProjName="Enter the name of your project: "

if not exist %ProjName%\\src MkDir %ProjName%\\src
copy "ToyRendererDistrubtionFiles\\SandBoxApp.cpp" "%ProjName%\\src\\SandBoxApp.cpp" /b/v/y

call premake\premake5.exe vs2017 --GameName="%ProjName%"
PAUSE