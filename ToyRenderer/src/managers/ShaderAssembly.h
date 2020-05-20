#pragma once
#include "Core.h"
#include <unordered_map>
#include <string>

namespace ToyRenderer{
	class TOYRENDERER_API ShaderAssembly {
    // PUBLIC ======================================================================================
	public:
		
	   	 ShaderAssembly();
		~ShaderAssembly();

		int GetShader(std::string shaderTag);
	 	

		bool LoadShaderInPath(const std::string& path);
		bool LoadAllShadersInFolder(const std::string& path);

	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
    #pragma warning( disable : 4251)  
	private:
		std::unordered_map<std::string, int>         m_CookedShaders;
    #pragma warning(default:4251) // Turning the 4251 back on
   };
}