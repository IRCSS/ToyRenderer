#pragma once
#include "rendering/Renderer.h"
#include <string>


class Texture {

public: 
	enum Filtering {
		Nearest, Linear, Nearest_MIP_Linear, Nearest_MIP_Nearest, Linear_MIP_Nearest, Linear_MIP_Linear
	};
	enum Wraping {
		Repeat, MirroredRepeat, ClampToEdge, ClampToBorder
	};

public:
	int AssetID;


private: 
	unsigned int   m_RendererID;
	std::string    m_FilePath;
	unsigned char* m_LocalBuffer;
	Filtering      m_filteringMode;
	Wraping        m_wrapingMode;
	int            m_Width;
	int            m_Height;
	int            m_BPP;


public:
	 Texture();
	 Texture(const std::string& path);
	~Texture();

	//Delete the copy constructor/assignment for All OpenGl Resources to avoid deleting reosurce on GPU on move/ coppy
	Texture(const Texture &) = delete;
	Texture &operator=(const Texture &) = delete;

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	inline int GetWidth()  const { return m_Width; };
	inline int GetHeight() const { return m_Height; };

private:
	void SetTextureParameters();


};