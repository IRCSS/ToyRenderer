#pragma once
class Material;
class Mesh;
class Texture;
#include <vector>

namespace ToyRenderer {

	class ResourceManager {

	public:

		static ResourceManager* resourceManagerSingelton;

	private:
		std::vector<Material*> r_materials;
		std::vector<Mesh*>     r_mesh;
		std::vector<Texture*>  r_texture;

	public:
		 ResourceManager();
		~ResourceManager(); //Delete all the resources in the destructor. 
		void RegisterMaterial(Material* mat);
		void RegisterMesh    (Mesh*     mesh);
		void RegisterTexture (Texture*  texture);

	private:

	};

}