#include "ResourceManager.h"
#include "Material.h"
#include "Mesh.h"
namespace ToyRenderer {

	ResourceManager* ResourceManager::m_pSingelton=nullptr;

	ResourceManager::ResourceManager() 
	{
	}
	void ResourceManager::RegisterMaterial(Material * mat)
	{
		//r_materials.push_back(mat);
		//mat->m_AssetID = resourceManagerSingelton->m_lastGivenAssetID;
		//resourceManagerSingelton->m_lastGivenAssetID++;
	}
	void ResourceManager::RegisterMesh(Mesh * mesh)
	{
		//r_mesh.push_back(mesh);
		//mesh->m_AssetID = resourceManagerSingelton->m_lastGivenAssetID;
		//resourceManagerSingelton->m_lastGivenAssetID++;
	}
	void ResourceManager::RegisterTexture(Texture * texture)
	{
		//r_texture.push_back(texture);
		//texture->AssetID = resourceManagerSingelton->m_lastGivenAssetID;
		//resourceManagerSingelton->m_lastGivenAssetID++;
	}
	ResourceManager & ResourceManager::Instance()
	{
		if (!m_pSingelton) m_pSingelton = new ResourceManager;

		return *m_pSingelton;

	}
}