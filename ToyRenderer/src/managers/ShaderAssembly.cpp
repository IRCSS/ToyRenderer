#include "ShaderAssembly.h"
#include "rendering/RHI/RHI.h"
#include <iostream>
#include <filesystem>
#include "managers/ShaderOven.h"
#include "log/Log.h"
#include "system/File.h"
namespace ToyRenderer {

	ShaderAssembly::ShaderAssembly()
	{
		// ------------------------------------------------------------------------------
		// Load All the Engine Resources

		std::string executablePath = std::string();
		TOYRENDERER_EXEPATH(executablePath);
		
		std::string filepath = executablePath + "/res/shaders";
		TOYRENDERER_STYLE_PATH(filepath);

		for (const auto & entry : std::filesystem::directory_iterator(filepath)) {
			CookedShader entryCooked = ShaderOven::CookShader(entry.path().string());
			m_CookedShaders[entryCooked.shaderTagName] = entryCooked.ProgramID;
		}
		// -------------------------------------------------------------------------------
		  
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
		ENGINE_LOG_WARN("Could not find the a shader named as: {}", shaderTag);

		return -1;
	}
}