#pragma once
#include "Core.h"
#include "Test.h"
#include "rendering/Shader.h"
#include "rendering/Renderer.h"
#include "rendering/Texture.h"
#include "rendering/VertexBufferLayout.h"
#include "rendering/VertexArray.h"
#include "Components/Transform.h"
#include "Components/Scripts/MoveCamera.h"
#include "world/Scene.h"

namespace ToyRenderer{
    namespace test {
    
    	class TOYRENDERER_API TesstObjLoader : public Test {

		// PUBLIC ======================================================================================
    	public:
    		 TesstObjLoader();
    		~TesstObjLoader();
    
    		void OnUpdate(float deltaTime) override;
    		void OnRender()                override;
    		void OnImGuiRender()           override;

		// ______________________________________________________________________________________________
		// PRIVATE ======================================================================================    
    	private:
    
    		Behaviours::MoveCamera* CameraMovment;
    		ToyRenderer::Transform* CameraViewTrabsform;
    		ToyRenderer::Scene*     pScene;
    
    	};
    }
}