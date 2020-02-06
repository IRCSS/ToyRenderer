#include "TestObjLoader.h"
#include "ResourceManager.h"
#include "MeshLoader.h"
#include "Mesh.h"
namespace test {
	TesstObjLoader::TesstObjLoader()
	{
		ToyRenderer::ResourceManager::Instance();


		ToyRenderer::RawMesh*  loadedMesh = ToyRenderer::MeshLoader::LoadTinyObj( "D:/ShaPlayGround/ToyRenderer/Meshes/WanderingMan_Model_CutOutMaster.obj", "D:/ShaPlayGround/ToyRenderer/Meshes/");
		
		if (loadedMesh)
		{
			std::cout << loadedMesh->m_subShapesCount << std::endl;

			std::vector<ToyRenderer::Mesh *> ms = loadedMesh->GenerateMeshes();
			if (ms.size()>0) std::cout << ms.size() << std::endl;

		}




	}
	TesstObjLoader::~TesstObjLoader()
	{
		ToyRenderer::ResourceManager::ClearResourceManager();
	}
}