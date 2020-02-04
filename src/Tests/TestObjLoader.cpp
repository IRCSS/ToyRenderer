#include "TestObjLoader.h"
#include "ResourceManager.h"
#include "MeshLoader.h"
namespace test {
	TesstObjLoader::TesstObjLoader()
	{
		ToyRenderer::ResourceManager::Instance();


		ToyRenderer::RawMesh*  loadedMesh = ToyRenderer::MeshLoader::LoadTinyObj( "D:/ShaPlayGround/ToyRenderer/Meshes/WanderingMan_Model_CutOutMaster.obj", "D:/ShaPlayGround/ToyRenderer/Meshes/");

		if(loadedMesh)
		std::cout << loadedMesh->m_subShapesCount << std::endl;
	}
	TesstObjLoader::~TesstObjLoader()
	{
		ToyRenderer::ResourceManager::ClearResourceManager();
	}
}