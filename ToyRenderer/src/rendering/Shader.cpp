#include "Shader.h"
#include "rendering/Renderer.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "log/Log.h"
#include "rendering/RHI/RHI.h"
#include "managers/ResourceManager.h"

namespace ToyRenderer{
    Shader::Shader(const std::string & shaderName) : m_shaderName(shaderName), m_RendererID(0)
    {
		m_RendererID = ResourceManager::Instance().shaderAssembly->GetShader(shaderName);
    }
    
    Shader::~Shader()
    {
    }
    
    void Shader::Bind() const
    {
		Rendering::RHI::SetProgramActive(m_RendererID);
    }
    
    void Shader::UnBind() const
    {
		Rendering::RHI::SetProgramActive(0);
    }
    
    void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
    {
    	int location = GetUniformLocation(name);
    	if (location == -1) return;
		Rendering::RHI::SetUniformFloat4(location, v0, v1, v2, v3);
    
    }
    
    void Shader::SetUniformf(const std::string & name, float v0)
    {
    	int location = GetUniformLocation(name);
    	if (location == -1) return;
		Rendering::RHI::SetUniformFloat(location, v0);
    }
    
    void Shader::SetUniform1i(const std::string& name, const int i0)
    {
    	int location = GetUniformLocation(name);
    	if (location == -1) return;
		Rendering::RHI::SetUniformInteger(location, i0);
    }
    
    void Shader::SetUniformMat4(const std::string & name, const glm::mat4 & Matrix)
    {
    	int location = GetUniformLocation(name);
    	if (location == -1) return;
		Rendering::RHI::SetUniformMatrix4F(location, &Matrix[0][0]);
    
    }
    
    int Shader::GetUniformLocation(const std::string& name)
    {
    
    	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) return m_UniformLocationCache[name];
    
		int location = Rendering::RHI::GetUniformLocation(m_RendererID, name.c_str());
    	m_UniformLocationCache[name] = location;
    	if(location == -1) ENGINE_LOG_WARN("RHI Warning: attempted to set Uniform {}. Uniform doesnt exist in shader {}", name, m_shaderName);
    
    	return location;
    }
}