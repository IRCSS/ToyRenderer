#include "TestObjLoader.h"
#include "ResourceManager.h"
#include "MeshLoader.h"
#include "Mesh.h"
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

		

		// Setting up the ground 

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






	}
	TesstObjLoader::~TesstObjLoader()
	{

		delete m_render;
		delete m_shader;

		delete m_va;
		delete m_ib;
		delete m_Texture;

		ToyRenderer::ResourceManager::ClearResourceManager();
	}


	void TesstObjLoader::OnUpdate(float deltaTime)
	{
	}
	void TesstObjLoader::OnRender()
	{
	}
	void TesstObjLoader::OnImGuiRender()
	{
	}
}