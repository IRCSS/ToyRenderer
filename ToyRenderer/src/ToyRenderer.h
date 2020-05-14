#pragma once

// CLIENT SIDE HEADER 

#include "ToyRendererApp.h"


// Utility
#include "log/Log.h"

// Managers
#include "managers/ResourceManager.h"

// World
#include "world/Scene.h"
#include "world/GameObject.h"

// System
#include "system/File.h"

// Components
#include "Components/Camera.h"
#include "Components/Scripts/postProcesses/Vignetting.h"

// Behaviours
#include "Components/Scripts/MoveCamera.h"
#include "Components/Scripts/ExitApplicationOnInput.h"

// Rendering
#include "rendering/Mesh/PrimitiveFactory.h"
#include "rendering/Shader.h"
#include "rendering/Material.h"
#include "rendering/RawMesh.h"

// Assets API
#include "importAPI/MeshLoader.h"

// Maths
#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"
#include "maths/Matrix4x4.h"

// Aduio
#include "Components/AudioPlayer.h" 
#include "Components/AudioListner.h"
