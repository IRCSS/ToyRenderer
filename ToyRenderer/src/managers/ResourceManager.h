#pragma once
#include "Core.h"
#include <vector>

namespace ToyRenderer {
    class Texture;
    class Shader;
	class Material;
	class Mesh;



	class TOYRENDERER_API ResourceManager {
	// PUBLIC ======================================================================================
	public:
		 ResourceManager();
		~ResourceManager(); //Delete all the resources in the destructor. 
		void RegisterMaterial(Material* mat);
		void RegisterMesh    (Mesh*     mesh);
		void RegisterTexture (Texture*  texture);
		void RegisterShader  (Shader*   shader);

		static ResourceManager& Instance();
		// Destroy the resource manager, next time you call instance you will create anew instance
		static void ClearResourceManager();
		
    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private:
		int GenerateAssetID();
    #pragma warning( disable : 4251)  
    // std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. Private stuff wont be inlined so I will disable them
	private:
		std::vector<Material*> r_materials;
		std::vector<Mesh*>     r_mesh;
		std::vector<Texture*>  r_texture;
		std::vector<Shader*>   r_shaders;
		
		int m_lastGivenAssetID;
		static ResourceManager *  m_pSingelton;

    #pragma warning(default:4251) // Turning the 4251 back on


	};

}