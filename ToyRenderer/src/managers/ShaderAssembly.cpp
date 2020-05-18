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
		
		std::string filepath = executablePath + "/res/engine/shaders";
		TOYRENDERER_STYLE_PATH(filepath);


		LoadAllShadersInFolder(filepath);

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
	bool ShaderAssembly::LoadShaderInPath(const std::string path)
	{
		if (!std::filesystem::exists(std::filesystem::path(path))) {

			ENGINE_LOG_WARN("Attempted to load a shader in folder {}, however no such folder exissts", path);
			return false;
		}

		CookedShader entryCooked = ShaderOven::CookShader(path);
		m_CookedShaders[entryCooked.shaderTagName] = entryCooked.ProgramID;

		return true;
	}
	bool ShaderAssembly::LoadAllShadersInFolder(const std::string & filepath)
	{
		if (!std::filesystem::exists(std::filesystem::path(filepath))) {
			
			ENGINE_LOG_WARN("Attempted to load a series of shaders in folder {}, however no such folder exissts", filepath);
			return false;
		}

		for (const auto & entry : std::filesystem::directory_iterator(filepath)) {
			if(!LoadShaderInPath(entry.path().string())) return false;
		}

		return true;
	}
}