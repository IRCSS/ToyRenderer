
Toyrenderer 
=================

ToyRenderer is a simple/ small sandbox engine written in C++. I use it as a starting point for experimenting with different ideas and graphic techniques and for learning more about C++ and engine development. The engine is under construction at the moment, from the readme, to the wiki and the code.

![screenshot](https://media.giphy.com/media/frNUWpMob0tjX9Pz3Z/giphy.gif)

It is made more for ease of use and setup than performance. I try to keep the code as simple as possible, avoid too many layers of abstraction and too many macros and templates. 

You can have a look at the [Wiki](https://github.com/IRCSS/ToyRenderer/wiki) for documentation, which is in the process of being written, the engine is going through a testing phase at the moment with a simple 2D game. 

Features that are already in the engine: 
- Automatic window creation and an easy to use build system to create a new applications with the engine
- A Scene/ Gameobjects/ Components/ Transforms system that makes scene constructions and creating new components very simple.
- Camera with a fully integrated Renderer that renders the objects in the scene
- Material system with support for different uniforms and render settings
- Shader system with support for settings defined in shaders
- An Audio Engine with 2D/3D audios with a simple AudioListener, AudioPlayer and AudioClips setup
- Input Master interface with input mapping and key querying functions. 
- Post Processing interface
- Procedural Skybox
- Mesh interface with procedural mesh generation as well as OBJ import
- Logging system with logging to both console and file
- Different Resource managers that take care of Assets memory management and lifetime 
- A Time class used for profiling as well as animation and game logic
- Render Hardware Interface abstraction for potentially supporting more Graphic APIs

Main Features planned for future:
- Physics engine integration
- Event System
- Frustum Culling
- Profiling tools
- Simple Scene Editor
- Asset Serialization



