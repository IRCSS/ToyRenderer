#pragma once
#include <string>
#include <unordered_map>
struct ParsedShader {
	std::string VertexSource;
	std::string FragmentSource;
};


;class Shader{

private: 
	unsigned int m_RendererID;
	std::string m_FilePath;
	//caching for uniform 
	std::unordered_map<std::string, unsigned int > m_UniformLocationCache;


public: 
	Shader(const std::string& fileName);
	~Shader();


	void Bind()   const;
	void UnBind() const;

	// Set Uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformf(const std::string& name, float v0);


private:
	         int GetUniformLocation(const std::string& name);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ParsedShader ParseShader(const std::string & filePath);
};