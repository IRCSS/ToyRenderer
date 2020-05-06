#include <ToyRenderer.h>

using namespace ToyRenderer;


class Sandbox : public ToyRenderer::ToyRendererApp {
public: 
	Sandbox() {
	
		CLIENT_LOG_INFO("sand box has been initialized");

		activeScene = new Scene();


		// ------------------------------------------------------------
		// Camera

		GameObject* cameraGB            = new GameObject();
		Transform*  CameraViewTransform = new Transform(Vector3(0.0f, -0.5f, 4.0f), vector3_one, Vector3(0., 0.0f, 0.0));
		cameraGB->AddComponent<Transform>(CameraViewTransform);

		ToyRenderer::Camera*  pCameraComp = new Camera(activeScene);
		PostProcessing::Vignetting* vignettingPos = new PostProcessing::Vignetting();
		pCameraComp->AddPostProcessToStack(vignettingPos);
		cameraGB->AddComponent<Camera>(pCameraComp);

		Behaviours::MoveCamera* CameraMovment = new Behaviours::MoveCamera(CameraViewTransform);
		cameraGB->AddComponent<Behaviours::MoveCamera>(CameraMovment);
		cameraGB->name = "mainCamera";
		activeScene->sceneObjects.push_back(cameraGB);

		// ------------------------------------------------------------
		// Setup GroundPlance

		GameObject*  groundGameObject = new GameObject();
		Transform*   groundGridTran   = new Transform(Vector3(0.0f, -4.5f, 4.0f), vector3_one*100.0f, vector3_zero);
		groundGameObject->AddComponent<Transform>(groundGridTran);

		ToyRenderer::Mesh* groundGridMesh = PrimitivFactory::CreatePlane();
		ToyRenderer::ResourceManager::Instance().RegisterMesh(groundGridMesh);
		Shader* gridShader = new Shader("unlit/groundGrid");

		Material* groundMaterial = new Material(gridShader);
		ResourceManager::Instance().RegisterMaterial(groundMaterial);


		groundMaterial->EnableBlend(true);
		groundMaterial->EnableZWrite(false);
		groundMaterial->SetRenderPass(Material_PASS_TRANSPARENT);
		groundMaterial->SetBlendFunc(Rendering::Blend_Function::SRC_ALPHA, Rendering::Blend_Function::ONE_MINUS_SRC_ALPHA);

		MeshRenderer* groundGridRend = new MeshRenderer(groundGridMesh, groundMaterial);

		groundGameObject->name = "groundPlane";

		groundGameObject->AddComponent<MeshRenderer>(groundGridRend);

		activeScene->sceneObjects.push_back(groundGameObject);

		// ------------------------------------------------------------
		// Cube Mesh Loading

		std::string resourceFolder = std::string();
		TOYRENDERER_EXEPATH(resourceFolder);

		resourceFolder += "/res/engine/meshes";
		TOYRENDERER_STYLE_PATH(resourceFolder);
		
		std::string fileName = (resourceFolder + "/unwraped_cube.obj");
		TOYRENDERER_STYLE_PATH(fileName);

         RawMesh*  loadedMesh = MeshLoader::LoadTinyObj(fileName.c_str(), resourceFolder.c_str());

		//ToyRenderer::RawMesh*  loadedMesh = ToyRenderer::MeshLoader::LoadTinyObj("D:/Meshes/MiniModel/Tatev/Tatev_1e+02KTris__4k_1Chunks_1xLOD.obj"
		//	, "D:/Meshes/MiniModel/Tatev");

		if (loadedMesh)
		{
			std::vector<Mesh *>       ms = loadedMesh->GenerateMeshes();
			Shader* unlit_texture_shader = new Shader("unlit/texture");

			ResourceManager::Instance().RegisterShader(unlit_texture_shader);

			for (int i = 0; i < ms.size(); i++) {

				// Owner ship by the pScene, it kills the objects later
				GameObject*    gb = new ToyRenderer::GameObject();
				int    materialID = loadedMesh->m_meshes_materials_ids[0];
				Material*   gbMat = loadedMesh->m_materials[materialID]; // already registered in resource manager on creation
				  gbMat->m_Shader = unlit_texture_shader;
				//gbMat->SetTwoSided(true);

				MeshRenderer* gbMeshRender = new MeshRenderer(ms[i], gbMat);

				Transform* gbTransform = new Transform(Vector3(0.0f, -10.5f, 0.0f), vector3_one, Vector3(-90.0f, 0.0f, 0.0f));

				gb->AddComponent<Transform>(gbTransform);
				gb->AddComponent<MeshRenderer>(gbMeshRender);

				activeScene->sceneObjects.push_back(gb);

			}

			//delete loadedMesh;
		}


		// Sound 
        // -------------------------------------------------------
		//SoLoud::Soloud gSoloud; // SoLoud engine
		//SoLoud::Wav gWave;      // One wave file

		//gSoloud.init(); // Initialize SoLoud

		//std::string pathToexe = std::string();
		//TOYRENDERER_EXEPATH(pathToexe);
		//std::string filepath = pathToexe + "\\res\\audio\\service-bell_daniel_simion.wav";
		//TOYRENDERER_STYLE_PATH(filepath);

		//SoLoud::result results = gWave.load(filepath.c_str()); // Load a wave
		//ENGINE_LOG_DEBUG("the loading result is: {}", results);
		//gSoloud.play(gWave); // Play the wave

		//AudioPlayer audioPlayerComponent("service-bell_daniel_simion.wav");
		//audioPlayerComponent.Play();



		// Update Camera Scene Content : Need a better solution later, maybe marking scene dirty or something
		pCameraComp->UpdateRenderLists();

	}
	~Sandbox() {

	}

};

ToyRenderer::ToyRendererApp* ToyRenderer::CreateApplication() 
{
	return new Sandbox();
}