#include "ShaderOven.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "log/Log.h"
#include "rendering/RHI/RHI.h"
#include "rendering/Renderer.h"

namespace ToyRenderer {

	CookedShader ShaderOven::CookShader(const std::string & pathToFile)
	{
		CookedShader toReturn;
		ParsedShader vfs = ParseShader(pathToFile);
		toReturn.shaderTagName = vfs.shaderTagName;

		toReturn.ProgramID = CreateShader(vfs.VertexSource, vfs.FragmentSource);

		return toReturn;
		
	}
	ParsedShader ShaderOven::ParseShader(const std::string & filePath)
	{
		std::ifstream stream(filePath);

		if (!stream.is_open()) ENGINE_LOG_ERROR("Assets Error: Attempted and failed to open, parse: {}", filePath);

		enum class ShaderParts {
			NONE = -1, VERTEX = 0, FRAGMENT = 1, SETTINGS = 2
		};

		std::string line;
		std::stringstream ss[2];
		ShaderParts currentShaderPart = ShaderParts::NONE;

		ParsedShader toReturn;

		while (getline(stream, line)) {

			if (line.find("SettingBegin") != std::string::npos) currentShaderPart = ShaderParts::SETTINGS;
			if (line.find("SettingEnd")   != std::string::npos) currentShaderPart = ShaderParts::NONE;

			if (currentShaderPart == ShaderParts::SETTINGS) {
				if (line.find("#tagName") != std::string::npos) toReturn.shaderTagName = line.substr(line.find("=") + 1);
			}
			else {
				if (line.find("#shader") != std::string::npos) {
					if (line.find("vertex") != std::string::npos) {
						// found vertex shader
						currentShaderPart = ShaderParts::VERTEX;
					}
					else if (line.find("fragment") != std::string::npos) {
						// found fragment shader
						currentShaderPart = ShaderParts::FRAGMENT;
					}
				}
				else if (currentShaderPart != ShaderParts::NONE) ss[(int)currentShaderPart] << line << '\n';
			}
		}

		if (toReturn.shaderTagName == "")
			ENGINE_LOG_ERROR("The Shader {}, does not have a name tag identifier. Add #tagName=desiredName to the .shader file!");

		toReturn.VertexSource   = ss[0].str();
		toReturn.FragmentSource = ss[1].str();

		return toReturn;

	}
	unsigned int ShaderOven::CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
	{
		unsigned int programID = Rendering::RHI::CreateProgram();
		unsigned int vs = CompileShader(Rendering::ShaderTypes::VERTEX_SHADER,   vertexShader);
		unsigned int fs = CompileShader(Rendering::ShaderTypes::FRAGMENT_SHADER, fragmentShader);


		Rendering::RHI::AttachShader(programID, vs);
		Rendering::RHI::AttachShader(programID, fs);
		
		Rendering::RHI::LinkProgram(programID);
		Rendering::RHI::ValidateProgram(programID);

		Rendering::RHI::DeleteShader(vs);
		Rendering::RHI::DeleteShader(fs);

		return programID;
	}
	unsigned int ShaderOven::CompileShader(Rendering::ShaderTypes type, const std::string & source)
	{
		
		unsigned int id = Rendering::RHI::CreateShader(type);
		const char*  src = source.c_str();
		Rendering::RHI::SetShaderSource(id, src);
		Rendering::RHI::CompileShader(id);
		Rendering::RHI::CheckCompilationShaderStatus(id, type);

		return id;
	}
}
