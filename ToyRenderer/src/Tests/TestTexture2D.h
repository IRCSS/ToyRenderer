#pragma once
#include "Core.h"
#include "Test.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/VertexArray.h"
#include "rendering/IndexBuffer.h" 
#include "rendering/Texture.h"

namespace ToyRenderer{
    namespace test {
    	class TOYRENDERER_API TestTexture2D : public Test {

		// PUBLIC ======================================================================================
    	public: 
    		TestTexture2D();
    		~TestTexture2D();
    
    		void OnUpdate(float deltaTime) override;
    		void OnRender()                override;
    		void OnImGuiRender()           override;

		// ______________________________________________________________________________________________
		// PRIVATE ====================================================================================== 
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
}