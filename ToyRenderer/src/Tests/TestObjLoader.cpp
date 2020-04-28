#include "TestObjLoader.h"
#include "managers/ResourceManager.h"
#include "importAPI/MeshLoader.h"
#include "rendering/Mesh/Mesh.h"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/imgui/imgui.h"
#include "managers/Settings.h"
#include "world/GameObject.h"
#include "rendering/Mesh/PrimitiveFactory.h"
#include "rendering/MeshRenderer.h"
#include "Components/Camera.h"
#include "rendering/Material.h"
#include "Components/Scripts/postProcesses/Vignetting.h"
namespace test {
	TesstObjLoader::TesstObjLoader()
	{
		ToyRenderer::ResourceManager::Instance();

		// Construct scene 
		pScene = new ToyRenderer::Scene();

		//// Construct Camera


		ToyRenderer::GameObject* cameraGB = new ToyRenderer::GameObject();
		CameraViewTrabsform = new ToyRenderer::Transform(Vector3(0.0f, -0.5f, 4.0f), vector3_one, Vector3(0., 0.0f, 0.0));
		cameraGB->AddComponent<ToyRenderer::Transform>(CameraViewTrabsform);

		ToyRenderer::Camera*  pCameraComp = new ToyRenderer::Camera(pScene);
		ToyRenderer::PostProcessing::Vignetting* vignettingPos = new ToyRenderer::PostProcessing::Vignetting();
		pCameraComp->AddPostProcessToStack(vignettingPos);
		cameraGB->AddComponent<ToyRenderer::Camera>(pCameraComp);

		CameraMovment       = new Behaviours::MoveCamera(CameraViewTrabsform);
		cameraGB->AddComponent < Behaviours::MoveCamera> (CameraMovment);
		cameraGB->name = "mainCamera";
		pScene->sceneObjects.push_back(cameraGB);


		// Setup GroundPlance
		ToyRenderer::GameObject*   groundGameObject = new ToyRenderer::GameObject();

		ToyRenderer::Transform*    groundGridTran   = new ToyRenderer::Transform(Vector3(0.0f, -4.5f, 4.0f), vector3_one*100.0f, vector3_zero);
		groundGameObject->AddComponent<ToyRenderer::Transform>(groundGridTran);

	    ToyRenderer::Mesh*  groundGridMesh = ToyRenderer::PrimitivFactory::CreatePlane();
		ToyRenderer::ResourceManager::Instance().RegisterMesh(groundGridMesh);
		Shader              *gridShader    = new Shader("res/shaders/groundGrid.shader");

        ToyRenderer::Material* groundMaterial = new ToyRenderer::Material(gridShader);
		ToyRenderer::ResourceManager::Instance().RegisterMaterial(groundMaterial);
		

		groundMaterial->EnableBlend  (true);
		groundMaterial->EnableZWrite (false);
		groundMaterial->SetRenderPass(Material_PASS_TRANSPARENT);

        ToyRenderer::MeshRenderer* groundGridRend = new ToyRenderer::MeshRenderer(groundGridMesh, groundMaterial);

		groundGameObject->name = "groundPlane";

		groundGameObject->AddComponent<ToyRenderer::MeshRenderer>(groundGridRend);

		pScene->sceneObjects.push_back(groundGameObject);


		





		ToyRenderer::RawMesh*  loadedMesh = ToyRenderer::MeshLoader::LoadTinyObj( "res/meshes/unwraped_cube.obj"
			, "res/meshes");

		//ToyRenderer::RawMesh*  loadedMesh = ToyRenderer::MeshLoader::LoadTinyObj("D:/Meshes/MiniModel/Tatev/Tatev_1e+02KTris__4k_1Chunks_1xLOD.obj"
		//	, "D:/Meshes/MiniModel/Tatev");
		
		if (loadedMesh)
		{
			std::vector<ToyRenderer::Mesh *> ms = loadedMesh->GenerateMeshes();
			Shader* unlit_texture_shader = new Shader("res/shaders/unlit_texture.shader");
				

			for (int i = 0; i < ms.size(); i++) {

				// Owner ship by the pScene, it kills the objects later
				ToyRenderer::GameObject*   gb = new ToyRenderer::GameObject();
				int materialID = loadedMesh->m_meshes_materials_ids[0];
				ToyRenderer::Material* gbMat = loadedMesh->m_materials[materialID]; // already registered in resource manager on creation
				gbMat->m_Shader = unlit_texture_shader;
				//gbMat->SetTwoSided(true);
				ToyRenderer::MeshRenderer* gbMeshRender = new ToyRenderer::MeshRenderer(ms[i], gbMat);

				ToyRenderer::Transform* gbTransform = new ToyRenderer::Transform(Vector3(0.0f, -10.5f, 0.0f), vector3_one, Vector3(-90.0f, 0.0f,0.0f));

				gb->AddComponent<ToyRenderer::Transform>(gbTransform);
				gb->AddComponent<ToyRenderer::MeshRenderer>(gbMeshRender);

				pScene->sceneObjects.push_back(gb);

			}

		}


		// Update Camera Scene Content : Need a better solution later, maybe marking scene dirty or something
		pCameraComp->UpdateRenderLists();

	}
	TesstObjLoader::~TesstObjLoader()
	{

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