#pragma once
#include "Core.h"
#include <string>
#include <unordered_map>
#include "vendor/glm/glm.hpp"

namespace ToyRenderer{



    class TOYRENDERER_API Shader{
	// PUBLIC ======================================================================================
    public: 
    	Shader(const std::string& shaderName);
    	~Shader();
    
    	//Delete the copy constructor/assignment for All OpenGl Resources to avoid deleting reosurce on GPU on move/ coppy
    	Shader(const Shader &) = delete;
    	Shader &operator=(const Shader &) = delete;
    
    
    	void Bind()   const;
    	void UnBind() const;
    
    	// Set Uniforms
    	void SetUniform4f  (const std::string& name, float v0, float v1, float v2, float v3);
    	void SetUniformf   (const std::string& name, float v0);
    	void SetUniform1i  (const std::string& name, const int i0);
    	void SetUniformMat4(const std::string& name, const glm::mat4& Matrix);

	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
    private: 
    #pragma warning( disable : 4251)  
    // std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. Private stuff wont be inlined so I will disable them
    	unsigned int m_RendererID;
    	std::string  m_shaderName;
    	//caching for uniform 
    	std::unordered_map<std::string, int > m_UniformLocationCache;
    #pragma warning(default:4251) // Turning the 4251 back on    
    private:
    	         int GetUniformLocation(const std::string& name);
    };
}