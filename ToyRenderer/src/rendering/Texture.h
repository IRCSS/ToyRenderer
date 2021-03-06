#pragma once

#include "Core.h"
#include "rendering/Renderer.h"
#include <string>

namespace ToyRenderer{

    class TOYRENDERER_API Texture {
	
	// PUBLIC ======================================================================================   
    public: 
    	enum Filtering {
    		Nearest, Linear, Nearest_MIP_Linear, Nearest_MIP_Nearest, Linear_MIP_Nearest, Linear_MIP_Linear
    	};
    	enum Wraping {
    		Repeat, MirroredRepeat, ClampToEdge, ClampToBorder
    	};
    
    	enum Format {
    		RGBA8, 
    	};
    
    public:
    	 Texture(const int width, const int heigth, const Filtering& filteringMode, const Wraping wrapingMode, Format bufferFormat);
    	 Texture(const std::string& path);
    	~Texture();
    
    	//Delete the copy constructor/assignment for All OpenGl Resources to avoid deleting reosurce on GPU on move/ coppy
    	Texture(const Texture &) = delete;
    	Texture &operator=(const Texture &) = delete;
    
    	void Bind(unsigned int slot = 0) const;
    	void UnBind() const;
    
    	unsigned int GetRenderID() const;
    
    	inline int GetWidth()  const { return m_Width; };
    	inline int GetHeight() const { return m_Height; };
    public:
    	int AssetID;
    
	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================    
    #pragma warning( disable : 4251)  
    // std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. Private stuff wont be inlined so I will disable them
    private: 
    	unsigned int   m_RendererID;
    	std::string    m_FilePath;
    	unsigned char* m_LocalBuffer;
    	Filtering      m_filteringMode;
    	Wraping        m_wrapingMode;
    	Format         m_format;
    	int            m_Width;
    	int            m_Height;
    	int            m_BPP;
    
    #pragma warning(default:4251) // Turning the 4251 back on  
    
    
    private:
    	void SetTextureParameters();
    	unsigned int GetInternalFormat();
    	/// relevant for pushing data in the GPU buffer
    	unsigned int GetDataFormat(); 
    
    };
}