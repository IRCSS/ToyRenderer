@echo off
set /p buildPath="Enter the path to where you wish to generate the release package: "
rem SET UP 
set solutionPath=%~dp0..\\..\\
cd /D "%buildPath%"

set vcvarsallPath="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat"

if not exist %vcvarsallPath% goto NOVCVARSALL

call %vcvarsallPath% x64_x86

echo "Starting Build for ToyRenderer"
echo .  
echo "Toyrender solution path: %solutionPath%\\ToyRenderer.sln"

devenv "%solutionPath%\\ToyRenderer.sln" /build Debug 
devenv "%solutionPath%\\ToyRenderer.sln" /build Release
devenv "%solutionPath%\\ToyRenderer.sln" /build Shipping

echo . 
echo "ToyRenderer build! Continueing with creating the release package."

rem Creating the package directory
if exist ToyRendererReleasePackage RMDIR /s /q ToyRendererReleasePackage 
mkdir ToyRendererReleasePackage

echo "solution directory is set as: %solutionPath%"

rem Copying premake
xcopy /Q /E /Y /I  "%solutionPath%vendor\\bin\\premake" ToyRendererReleasePackage\\premake

mkdir ToyRendererReleasePackage\\ToyRendererDistrubtionFiles

rem Coppying the header files
ROBOCOPY "%solutionPath%ToyRenderer\\src\\" ToyRendererReleasePackage\\include\\ *.h *.hpp *.inl /S

rem copying the dll for debug, release 

if not exist "%solutionPath%ToyRenderer-binaries\\Release-windows-x86_64" echo "WARNING: the release configuration is not build, please first build in VS in Release configuration"

echo "coppying over the ToyRenderer dll in Release mode from %solutionPath%ToyRenderer-binaries\\Release-windows-x86_64\\ToyRenderer ToyRendererReleasePackage\\ToyRendererDistrubtionFiles\\ToyRenderer-Release"

xcopy /Q /E /Y /I  "%solutionPath%ToyRenderer-binaries\\Release-windows-x86_64\\ToyRenderer" ToyRendererReleasePackage\\ToyRendererDistrubtionFiles\\ToyRenderer-Release

if not exist "%solutionPath%ToyRenderer-binaries\\Debug-windows-x86_64 echo" "WARNING: the Debug configuration is not build, please first build in VS in Debug configuration"

echo "coppying over the ToyRenderer dll in Debug  mode from  %solutionPath%ToyRenderer-binaries\\Debug-windows-x86_64\\ToyRenderer ToyRendererReleasePackage\\ToyRendererDistrubtionFiles\\ToyRenderer-Debug"

xcopy /Q /E /Y /I  "%solutionPath%ToyRenderer-binaries\\Debug-windows-x86_64\\ToyRenderer" ToyRendererReleasePackage\\ToyRendererDistrubtionFiles\\ToyRenderer-Debug

echo "coppying over the ToyRenderer dll in Shipping  mode from  %solutionPath%ToyRenderer-binaries\\Shipping-windows-x86_64\\ToyRenderer ToyRendererReleasePackage\\ToyRendererDistrubtionFiles\\ToyRenderer-Shipping"

xcopy /Q /E /Y /I  "%solutionPath%ToyRenderer-binaries\\Shipping-windows-x86_64\\ToyRenderer" ToyRendererReleasePackage\\ToyRendererDistrubtionFiles\\ToyRenderer-Shipping

rem Copying the res folder of the Engine 

echo "coppying over the ToyRenderer res folder from %solutionPath%ToyRenderer\\res to ToyRendererReleasePackage\\ToyRendererDistrubtionFiles\\res\\engine"

xcopy /Q /E /Y /I "%solutionPath%ToyRenderer\\res" ToyRendererReleasePackage\\ToyRendererDistrubtionFiles\\res\\engine

rem Copying the res folder of sand box as starter content

echo "coppying over the Sandbox res folder from  %solutionPath%example\\SandBox\\res to ToyRendererReleasePackage\\ToyRendererStarterContent\\res"

xcopy /Q /E /Y /I "%solutionPath%example\\SandBox\\res" ToyRendererReleasePackage\\ToyRendererStarterContent\\res\\game

rem Copying over the starter content CPP, aka the SandBox.CPP

echo "coppying over the Sandbox.cpp from  %solutionPath%example\\SandBox\\src\\SandBoxApp.cpp to ToyRendererReleasePackage\\ToyRendererStarterContent\\SandBoxApp.cpp"

xcopy /Q /E /Y /I "%solutionPath%example\\SandBox\\src" ToyRendererReleasePackage\\ToyRendererStarterContent

rem Copying over the project generation files 

echo "coppying over the project generation from  %solutionPath%ReleaseUtility\\ClientProjectGeneration to ToyRendererReleasePackage"

xcopy /Q /E /Y /I "%solutionPath%ReleaseUtility\\ClientProjectGeneration" ToyRendererReleasePackage

goto SUCCESSFULEND


:NOVCVARSALL

echo "The path specified to the VCVRSALL bat file which sets up the vc paths and variables is invalid. Path: %vcvarsallPath%"

goto EOF

:SUCCESSFULEND

echo "Build Completed!"



:EOF

PAUSE
