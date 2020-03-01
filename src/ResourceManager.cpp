#include "ResourceManager.h"
#include "rendering/Material.h"
#include "rendering/Mesh/Mesh.h"
namespace ToyRenderer {

	ResourceManager* ResourceManager::m_pSingelton=nullptr;

	ResourceManager::ResourceManager() 
	{
	}
	ResourceManager::~ResourceManager()
	{
		for (std::vector<Texture*>::iterator i = r_texture.begin(); i != r_texture.end(); ++i)
			delete *i;
		r_texture.clear();

		for (std::vector<Mesh*>::iterator i = r_mesh.begin(); i != r_mesh.end(); ++i)
			delete *i;
		r_mesh.clear();

		for (std::vector<Material*>::iterator i = r_materials.begin(); i != r_materials.end(); ++i)
			delete *i;
		r_materials.clear();

	}
	void ResourceManager::RegisterMaterial(Material * mat)
	{
		r_materials.push_back(mat);
		mat->m_AssetID = GenerateAssetID();
	}
	void ResourceManager::RegisterMesh(Mesh * mesh)
	{
		r_mesh.push_back(mesh);
		mesh->m_AssetID = GenerateAssetID();
	}
	void ResourceManager::RegisterTexture(Texture * texture)
	{
		r_texture.push_back(texture);
		texture->AssetID = GenerateAssetID();
	}
	ResourceManager & ResourceManager::Instance()
	{
		if (!m_pSingelton) m_pSingelton = new ResourceManager;

		return *m_pSingelton;

	}
	void ResourceManager::ClearResourceManager()
	{
		delete m_pSingelton;

	}
	int ResourceManager::GenerateAssetID()
	{
		int id = m_lastGivenAssetID;
		m_lastGivenAssetID++;
		return id;
	}
}