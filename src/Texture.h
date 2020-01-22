#pragma once
#include "Renderer.h"
#include <string>
class Texture {

public:
	int AssetID;

private: 
	unsigned int   m_RendererID;
	std::string    m_FilePath;
	unsigned char* m_LocalBuffer;
	int            m_Width;
	int            m_Height;
	int            m_BPP;


public:
	 Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth()  const { return m_Width; };
	inline int GetHeight() const { return m_Height; };


};