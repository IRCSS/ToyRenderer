#pragma once
#include "Core.h"
#include <string>
#include <unordered_map>
#include "vendor/glm/glm.hpp"

namespace ToyRenderer{

    struct ParsedShader {
    	std::string VertexSource;
    	std::string FragmentSource;
    };

    class TOYRENDERER_API Shader{
	// PUBLIC ======================================================================================
    public: 
    	Shader(const std::string& fileName);
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
    	unsigned int m_RendererID;
    	std::string  m_FilePath;
    	//caching for uniform 
    	std::unordered_map<std::string, int > m_UniformLocationCache;
    
    private:
    	         int GetUniformLocation(const std::string& name);
    	unsigned int CreateShader      (const std::string& vertexShader, const std::string& fragmentShader);
    	unsigned int CompileShader     (unsigned int type, const std::string& source);
    	ParsedShader ParseShader       (const std::string & filePath);
    };
}