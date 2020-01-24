#pragma once

#include <vector>
class Texture;

namespace ToyRenderer {
	class Material;
	class Mesh;


	class ResourceManager {

	public:

		

	private:
		std::vector<Material*> r_materials;
		std::vector<Mesh*>     r_mesh;
		std::vector<Texture*>  r_texture;
		
		int m_lastGivenAssetID;
		static ResourceManager *  m_pSingelton;

	public:
		 ResourceManager();
		~ResourceManager(); //Delete all the resources in the destructor. 
		void RegisterMaterial(Material* mat);
		void RegisterMesh    (Mesh*     mesh);
		void RegisterTexture (Texture*  texture);


		static ResourceManager& Instance();

	private:

		int GenerateAssetID();
	};

}