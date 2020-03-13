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
#include "Components/Camera.h"
#include "rendering/Material.h"
namespace test {
	TesstObjLoader::TesstObjLoader()
	{
		ToyRenderer::ResourceManager::Instance();

		// Construct scene 
		pScene = new ToyRenderer::Scene();

		// Construct Camera


		ToyRenderer::GameObject* cameraGB = new ToyRenderer::GameObject();
		CameraViewTrabsform = new ToyRenderer::Transform(Vector3(0.0f, -0.5f, 4.0f), vector3_one, Vector3(0., 0.0f, 0.0));
		cameraGB->AddComponent<ToyRenderer::Transform>(CameraViewTrabsform);

		ToyRenderer::Camera*  pCameraComp = new ToyRenderer::Camera(pScene);
		cameraGB->AddComponent<ToyRenderer::Camera>(pCameraComp);

		CameraMovment       = new Behaviours::MoveCamera(CameraViewTrabsform);
		cameraGB->AddComponent < Behaviours::MoveCamera> (CameraMovment);
		cameraGB->name = "mainCamera";
		pScene->sceneObjects.push_back(cameraGB);


		// Setup GroundPlance
		ToyRenderer::GameObject*   groundGameObject = new ToyRenderer::GameObject();

		ToyRenderer::Transform*    groundGridTran = new ToyRenderer::Transform(Vector3(0.0f, -4.5f, 4.0f), vector3_one*100.0f, vector3_zero);
		groundGameObject->AddComponent<ToyRenderer::Transform>(groundGridTran);

	    ToyRenderer::Mesh*         groundGridMesh = ToyRenderer::PrimitivFactory::CreatePlane();
		                                 m_shader = new Shader("res/shaders/basic.shader");

        ToyRenderer::Material*     groundMaterial = new ToyRenderer::Material(m_shader);
		ToyRenderer::ResourceManager::Instance().RegisterMaterial(groundMaterial);
        
        ToyRenderer::MeshRenderer* groundGridRend = new ToyRenderer::MeshRenderer(groundGridMesh, groundMaterial);

		groundGameObject->name = "groundPlane";

		groundGameObject->AddComponent<ToyRenderer::MeshRenderer>(groundGridRend);

		pScene->sceneObjects.push_back(groundGameObject);


		



		// Update Camera Scene Content : Need a better solution later, maybe marking scene dirty or something
		pCameraComp->UpdateRenderLists();

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
		pScene->sceneObjects[1]->GetComponent<ToyRenderer::MeshRenderer>()->material->SetFloat("u_iTime", deltaTime);
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