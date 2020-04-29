#include "TestTexture2D.h"
#include "rendering/Renderer.h"
#include "vendor/imgui/imgui.h"
#include "rendering/VertexBuffer.h"

#include "rendering/VertexBufferLayout.h"

namespace ToyRenderer{
    namespace test {
    	TestTexture2D::TestTexture2D() : translation(0.0f, 1.0f, 0.0f), m_shader("res/shaders/basic.shader")
    	{
    		
    		// Vertex layout, vec2 positions (2 floats), vec2 uv (2 floats), maybe move this to a struct of a sort later
    		m_render = Renderer();
    		float positions[] = {
    			-1.0f, -1.0f, 0.0f, 0.0f, // 0
    			 1.0f, -1.0f, 1.0f, 0.0f, // 1
    			 1.0f,  1.0f, 1.0f, 1.0f, // 2
    			-1.0f,  1.0f, 0.0f, 1.0f  // 3
    		};
    
    		unsigned int traingleIndcies[] =
    		{
    			0, 1 ,2, // first Triagnle 
    			2, 3, 0, // second Triangle
    		};
    
    
    		// Need to abstract this later to an obejct of a sort. The shader stuff and uniforms need 
    	    // to go to a matrial and the vertex array and vertexbuffer need to be constructed from a 
    	    // mesh and a meshRenderer class of a sort
    
    		
    		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
    
    		m_ib= new IndexBuffer(traingleIndcies, 6);
    
    
    		// to do: add semantics to layout for ease of API use later
    		VertexBufferLayout layout;
    		layout.Push<float>(2); // position
    		layout.Push<float>(2); // uv
    		m_va.AddBuffer(vb, layout);
    
    		m_proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    
    		m_view = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    
    		glm::vec3 translation(0.0f, 1.0f, 0.0f);
    		m_model = glm::translate(glm::mat4(1.0f), translation);
    		m_mvp = m_proj * m_view * m_model;
    
    		m_shader.Bind();
    		m_shader.SetUniform1i("u_Texture", 0); // binding the texture to the 0 slot of the sampler2D
    
    
    		 m_Texture = new Texture("res/textures/checkerFormat.png");
    		 m_Texture->Bind();
    
    		m_va.UnBind();
    		vb.UnBind();
    		m_ib->UnBind();
    		m_shader.UnBind();
    
    
    
    	}
    	TestTexture2D::~TestTexture2D()
    	{
    		delete m_Texture;
    		delete m_ib;
    	}
    	void TestTexture2D::OnUpdate(float deltaTime)
    	{
    	}
    	void TestTexture2D::OnRender()
    	{
    		m_shader.Bind();
    		m_shader.SetUniformf("u_iTime", 0.0f); // need to abstract his in material class
    		m_model = glm::translate(glm::mat4(1.0f), translation);
    		m_mvp   = m_proj * m_view * m_model;
    		m_shader.SetUniformMat4("u_MVP", m_mvp);
    
    		m_render.Draw(m_va, *m_ib, m_shader);
    
    	}
    	void TestTexture2D::OnImGuiRender()
    	{
    		{
    			ImGui::SliderFloat3("float", &translation.x, -2.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
    			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    		}
    
    	}
    }
}