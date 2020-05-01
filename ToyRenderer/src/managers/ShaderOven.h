#pragma once
#include "Core.h"
#include <string>
#include "rendering/RHI/RenderingPipelineTypes.h"
namespace ToyRenderer {

	struct ParsedShader {
		std::string shaderTagName;
		std::string VertexSource;
		std::string FragmentSource;
	};

	struct CookedShader {
		int ProgramID;
		std::string shaderTagName;
	};

	static class TOYRENDERER_API ShaderOven{

			
	// PUBLIC ======================================================================================
	public: 

		static CookedShader CookShader(const std::string& pathToFile);
	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================

	private:

		static ParsedShader ParseShader  (const std::string & filePath);
		static unsigned int CreateShader (const std::string& vertexShader, const std::string& fragmentShader);
		static unsigned int CompileShader(Rendering::ShaderTypes type, const std::string& source);

	};

}