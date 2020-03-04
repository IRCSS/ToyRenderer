#include "TestObjLoader.h"
#include "ResourceManager.h"
#include "MeshLoader.h"
#include "rendering/Mesh/Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "Settings.h"
namespace test {
	TesstObjLoader::TesstObjLoader()
	{
		ToyRenderer::ResourceManager::Instance();


		//ToyRenderer::RawMesh*  loadedMesh = ToyRenderer::MeshLoader::LoadTinyObj( "D:/ShaPlayGround/ToyRenderer/Meshes/WanderingMan_Model_CutOutMaster.obj", "D:/ShaPlayGround/ToyRenderer/Meshes/");
		//
		//if (loadedMesh)
		//{
		//	std::cout << loadedMesh->m_subShapesCount << std::endl;

		//	std::vector<ToyRenderer::Mesh *> ms = loadedMesh->GenerateMeshes();
		//	if (ms.size()>0) std::cout << ms.size() << std::endl;

		//}

		// Setting up shader for Rendering 
		m_render = new Renderer();

		m_shader = new Shader("res/shaders/basic.shader");
		



		// Setting up the ground 

		float positions[] = {
			-1.0f, -1.0f, 3.5f, 0.0f, 0.0f, // 0
			 1.0f, -1.0f, 3.5f, 1.0f, 0.0f, // 1
			 1.0f,  1.0f, 0.5f, 1.0f, 1.0f, // 2
			-1.0f,  1.0f, 0.5f, 0.0f, 1.0f  // 3
		};

		unsigned int traingleIndcies[] =
		{
			0, 1 ,2, // first Triagnle 
			2, 3, 0, // second Triangle
		};


		VertexBuffer vb(positions, 5 * 4 * sizeof(float));

		m_ib = new IndexBuffer(traingleIndcies, 6);

		VertexBufferLayout layout;
		layout.Push<float>(3); // position
		layout.Push<float>(2); // uv

		m_va = new VertexArray();
		m_va->AddBuffer(vb, layout);


		//m_proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

		m_proj = glm::perspective(glm::radians(60.0f), (float)Settings::WindowWidth / (float)Settings::WindowHeigth, 0.1f, 100.0f);

		CameraViewTrabsform = new ToyRenderer::Transform(Vector3(0.0f, -0.5f,  4.0f), vector3_one, Vector3(0., 0.0f, 0.0));
		CameraMovment       = new Behaviours::MoveCamera(CameraViewTrabsform);

		m_view = CameraViewTrabsform->worldToLocal().GetGLM();

		glm::vec3 translation(0.0f, 1.0f, 0.0f);
		m_model = glm::translate(glm::mat4(1.0f), translation);
		m_mvp = m_proj * m_view * m_model;


		m_shader->Bind();
		m_shader->SetUniform1i("u_Texture", 0); // binding the texture to the 0 slot of the sampler2D


		m_Texture = new Texture("res/textures/checkerFormat.png");
		m_Texture->Bind();


		m_va->UnBind();
		vb.UnBind();
		m_ib->UnBind();
		m_shader->UnBind();
	}
	TesstObjLoader::~TesstObjLoader()
	{

		delete m_render;
		delete m_shader;

		delete m_va;
		delete m_ib;

		delete CameraMovment;
		delete CameraViewTrabsform;

		ToyRenderer::ResourceManager::ClearResourceManager();
	}


	void TesstObjLoader::OnUpdate(float deltaTime)
	{
		CameraMovment->OnUpdate(deltaTime);

	}
	void TesstObjLoader::OnRender()
	{
		m_shader->Bind();
		m_shader->SetUniformf("u_iTime", 0.0f); // need to abstract his in material class
		m_model = glm::translate(glm::mat4(1.0f), translation);
		m_view = CameraViewTrabsform->worldToLocal().GetGLM();



		m_mvp = m_proj * m_view * m_model;

		m_shader->SetUniformMat4("u_MVP", m_mvp);

		m_render->Draw(*m_va, *m_ib, *m_shader);

	}
	void TesstObjLoader::OnImGuiRender()
	{
		ImGui::SliderFloat3("float", &translation.x, -2.0f, 2.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}