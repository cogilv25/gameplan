# Gameplan

A template for making games in C++ using OpenGL, ImGui, GLM and GLFW.

## How do I build it

### Windows
- Install [Visual Studio 2022](https://visualstudio.microsoft.com/vs/)
	- Make sure you install support for C++ development
- Install [premake5](https://premake.github.io/download/)
	- Download the latest exe and put it anywhere on your system
	- Add it to the PATH environment variable
- Download this repository on to your computer
- Navigate to the folder containing Gameplan's files in a terminal window
- Type `premake5 vs2022`
- Open the solution file created in Visual Studio 2022
- Press F5 to build all projects and launch the test project