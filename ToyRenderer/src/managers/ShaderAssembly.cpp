#include "ShaderAssembly.h"
#include "rendering/RHI/RHI.h"
#include "ShaderOven.h"
#include <iostream>
#include <filesystem>
#include "log/Log.h"
#include "managers/ShaderOven.h"
namespace ToyRenderer {
	ShaderAssembly::ShaderAssembly()
	{
		std::string pathToResourcesFolder = "D:/ShaPlayGround/ToyRenderer/ToyRenderer/ToyRenderer/res/shaders";
		for (const auto & entry : std::filesystem::directory_iterator(pathToResourcesFolder)) {
			CookedShader entryCooked = ShaderOven::CookShader(entry.path().string());
			m_CookedShaders[entryCooked.shaderTagName] = entryCooked.ProgramID;
		
		}
		  
	}
	ShaderAssembly::~ShaderAssembly()
	{

	   // Iterate over an unordered_map using range based for loop
	   for (std::pair<std::string, int> element : m_CookedShaders)
	   {
		   Rendering::RHI::DeleteProgram(element.second);
	   }

	   m_CookedShaders.clear();
	}
	int ShaderAssembly::GetShader(std::string shaderTag)
	{
		if (m_CookedShaders.find(shaderTag) != m_CookedShaders.end()) return m_CookedShaders[shaderTag];
		ENGINE_LOG_INFO("Could not find the a shader named as: {}", shaderTag);

		return -1;
	}
}