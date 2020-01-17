#pragma once
#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

namespace test {
	class TestTexture2D : public Test {
	public: 
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender()                override;
		void OnImGuiRender()           override;

	private:

		glm::vec3 translation;
		Renderer m_render;
		Shader m_shader;

		VertexArray  m_va;
		IndexBuffer* m_ib;
		Texture*     m_Texture;

		glm::mat4 m_model;
		glm::mat4 m_proj;
		glm::mat4 m_view;
		glm::mat4 m_mvp;
	};
}