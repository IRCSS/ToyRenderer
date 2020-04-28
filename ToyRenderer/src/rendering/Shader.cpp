#include "Shader.h"
#include "rendering/Renderer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "log/Log.h"

namespace ToyRenderer{
    Shader::Shader(const std::string & fileName) : m_FilePath(fileName), m_RendererID(0)
    {
    	ParsedShader vfs = ParseShader(fileName);
    	m_RendererID = CreateShader(vfs.VertexSource, vfs.FragmentSource);
    
    
    }
    
    Shader::~Shader()
    {
    	GlCall(glDeleteProgram(m_RendererID));
    }
    
    void Shader::Bind() const
    {
    	GlCall(glUseProgram(m_RendererID));
    }
    
    void Shader::UnBind() const
    {
    	GlCall(glUseProgram(0));
    }
    
    void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
    {
    	int location = GetUniformLocation(name);
    	if (location == -1) return;
    	GlCall(glUniform4f(location, v0, v1, v2, v3));
    
    }
    
    void Shader::SetUniformf(const std::string & name, float v0)
    {
    	int location = GetUniformLocation(name);
    	if (location == -1) return;
    	GlCall(glUniform1f(location, v0));
    }
    
    void Shader::SetUniform1i(const std::string& name, const int i0)
    {
    	int location = GetUniformLocation(name);
    	if (location == -1) return;
    	GlCall(glUniform1i(location, i0));
    }
    
    void Shader::SetUniformMat4(const std::string & name, const glm::mat4 & Matrix)
    {
    	int location = GetUniformLocation(name);
    	if (location == -1) return;
    	GlCall(glUniformMatrix4fv(location, 1, GL_FALSE, &Matrix[0][0]));
    
    }
    
    
    
    int Shader::GetUniformLocation(const std::string& name)
    {
    
    	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) return m_UniformLocationCache[name];
    
    	GlCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    	m_UniformLocationCache[name] = location;
    	if(location == -1) ENGINE_LOG_WARN("RHI Warning: attempted to set Uniform {}. Uniform doesnt exist in shader {}", name, m_FilePath);
    
    	return location;
    }
    
    
    
    
    
    ParsedShader Shader::ParseShader(const std::string & filePath) {
    	std::ifstream stream(filePath);
    	
    	if (!stream.is_open()) ENGINE_LOG_ERROR("Assets Error: Attempted and failed to open, parse: {}", filePath);
    
    	enum class ShaderType {
    		NONE = -1, VERTEX = 0, FRAGMENT = 1
    	};
    
    	std::string line;
    	std::stringstream ss[2];
    	ShaderType currentShaderType = ShaderType::NONE;
    
    
    	while (getline(stream, line)) {
    
    
    		if (line.find("#shader") != std::string::npos) {
    			if (line.find("vertex") != std::string::npos) {
    				// found vertex shader
    				currentShaderType = ShaderType::VERTEX;
    			}
    			else if (line.find("fragment") != std::string::npos) {
    				// found fragment shader
    				currentShaderType = ShaderType::FRAGMENT;
    			}
    		}
    		else {
    
    			ss[(int)currentShaderType] << line << '\n';
    		}
    	}
    
    
    	return { ss[0].str(), ss[1].str() };
    
    }
    
    
    
    unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    	GlCall(unsigned int programID = glCreateProgram());
    	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    
    
    	GlCall(glAttachShader(programID, vs));
    	GlCall(glAttachShader(programID, fs));
    
    	GlCall(glLinkProgram(programID));
    	GlCall(glValidateProgram(programID));
    
    	GlCall(glDeleteShader(vs));
    	GlCall(glDeleteShader(fs));
    
    
    
    	return programID;
    }
    
    unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    	unsigned int id = glCreateShader(type);
    	const char*  src = source.c_str();
    	glShaderSource(id, 1, &src, nullptr);
    	glCompileShader(id);
    
    	int result;
    	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    	if (result == GL_FALSE) {
    		int length;
    		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    		char* message = (char*)alloca(length * sizeof(char));
    		glGetShaderInfoLog(id, length, &length, message);
    
    		ENGINE_LOG_ERROR("RHI ERROR: Failed to compile {} shader! message: {}", (type == GL_VERTEX_SHADER ? "vertex " : "fragment "), message);
    
    
    		glDeleteShader(id);
    		return 0;
    	}
    
    	return id;
    }
}