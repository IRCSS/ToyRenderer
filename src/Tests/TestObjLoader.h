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


		glm::vec3  translation;
		Renderer*  m_render;
		Shader*    m_shader;

		VertexArray *m_va;
		IndexBuffer *m_ib;
		Texture     *m_Texture;

		Behaviours::MoveCamera* CameraMovment;
		ToyRenderer::Transform* CameraViewTrabsform;
		ToyRenderer::Scene*     pScene;


		glm::mat4 m_model;
		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::mat4 m_mvp;

	
	};
}