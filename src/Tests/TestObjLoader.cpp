#include "TestObjLoader.h"
#include "ResourceManager.h"
#include "MeshLoader.h"
#include "rendering/Mesh/Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "Settings.h"
#include "world/GameObject.h"
#include "rendering/Mesh/PrimitiveFactory.h"
#include "rendering/MeshRenderer.h"
namespace test {
	TesstObjLoader::TesstObjLoader()
	{
		ToyRenderer::ResourceManager::Instance();

		// Construct scene 
		pScene = new ToyRenderer::Scene();

		// Construct Camera


		ToyRenderer::GameObject* cameraGB = new ToyRenderer::GameObject();
		CameraViewTrabsform = new ToyRenderer::Transform(Vector3(0.0f, -0.5f, 4.0f), vector3_one, Vector3(0., 0.0f, 0.0));
		cameraGB->AddComponent(CameraViewTrabsform);

		CameraMovment       = new Behaviours::MoveCamera(CameraViewTrabsform);
		cameraGB->AddComponent(CameraMovment);
		cameraGB->name = "mainCamera";
		pScene->sceneObjects.push_back(cameraGB);


		// Setup GroundPlance
		ToyRenderer::GameObject*   groundGameObject = new ToyRenderer::GameObject();

		ToyRenderer::Transform*    groundGridTran = new ToyRenderer::Transform(Vector3(0.0f, -4.5f, 4.0f), vector3_one*100.0f, vector3_zero);
		groundGameObject->AddComponent(groundGridTran);

	    ToyRenderer::Mesh*         groundGridMesh = ToyRenderer::PrimitivFactory::CreatePlane();
		                                 m_shader = new Shader("res/shaders/basic.shader");
        ToyRenderer::MeshRenderer* groundGridRend = new ToyRenderer::MeshRenderer(groundGridMesh, m_shader);

	

		groundGameObject->AddComponent(groundGridRend);

		pScene->sceneObjects.push_back(groundGameObject);

		//ToyRenderer::RawMesh*  loadedMesh = ToyRenderer::MeshLoader::LoadTinyObj( "D:/ShaPlayGround/ToyRenderer/Meshes/WanderingMan_Model_CutOutMaster.obj", "D:/ShaPlayGround/ToyRenderer/Meshes/");
		//
		//if (loadedMesh)
		//{
		//	std::cout << loadedMesh->m_subShapesCount << std::endl;

		//	std::vector<ToyRenderer::Mesh *> ms = loadedMesh->GenerateMeshes();
		//	if (ms.size()>0) std::cout << ms.size() << std::endl;

		//}

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
		pScene->OnUpdate(deltaTime);

	}
	void TesstObjLoader::OnRender()
	{
		pScene->OnRender();
	}
	void TesstObjLoader::OnImGuiRender()
	{
	}
}