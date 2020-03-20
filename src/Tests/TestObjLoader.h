#pragma once
#include "Test.h"
#include "Shader.h"
#include "rendering/Renderer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
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