#pragma once
#include "Test.h"
#include "rendering/Shader.h"
#include "rendering/Renderer.h"
#include "rendering/Texture.h"
#include "rendering/VertexBufferLayout.h"
#include "rendering/VertexArray.h"
#include "Components/Transform.h"
#include "Components/Scripts/MoveCamera.h"
#include "world/Scene.h"

namespace test {

	class TesstObjLoader : public Test {
	public:
		 TesstObjLoader();
		~TesstObjLoader();

		void OnUpdate(float deltaTime) override;
		void OnRender()                override;
		void OnImGuiRender()           override;

	private:




		Behaviours::MoveCamera* CameraMovment;
		ToyRenderer::Transform* CameraViewTrabsform;
		ToyRenderer::Scene*     pScene;



	
	};
}