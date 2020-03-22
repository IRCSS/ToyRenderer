#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const int width, const int heigth, const Filtering& filteringMode, const Wraping wrapingMode, Format bufferFormat):
	m_RendererID(0), m_FilePath(""), m_LocalBuffer(nullptr),
	m_Width(width), m_Height(heigth), m_BPP(0)
{
	GlCall(glGenTextures(1, &m_RendererID));

	m_wrapingMode   = wrapingMode;
	m_filteringMode = filteringMode;

	// TEXTURE IS BINDED IN THE SetTextureParameters Function. If you move this function, make sure to bind before the TexImage2D call
	SetTextureParameters();

	m_format = bufferFormat;

	GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GetInternalFormat(), m_Width, m_Height, 0, GetDataFormat(), GL_UNSIGNED_BYTE, 0));
	UnBind();
}

Texture::Texture(const std::string& path):
	m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{

	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GlCall(glGenTextures(1, &m_RendererID));

	m_wrapingMode   = Wraping::ClampToEdge;
	m_filteringMode = Filtering::Linear;

	// TEXTURE IS BINDED IN THE SetTextureParameters Function. If you move this function, make sure to bind before the TexImage2D call
	SetTextureParameters();
	
	m_format = Format::RGBA8;

	GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GetInternalFormat(), m_Width, m_Height, 0, GetDataFormat(), GL_UNSIGNED_BYTE, m_LocalBuffer));
	UnBind();

	if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);

}

Texture::~Texture()
{
	GlCall(glDeleteTextures(1, &m_RendererID));

}

void Texture::Bind(unsigned int slot) const
{
	GlCall(glActiveTexture(GL_TEXTURE0 + slot));
	GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::UnBind() const
{
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));

}

unsigned int Texture::GetRenderID() const
{
	return m_RendererID;
}

void Texture::SetTextureParameters()
{

	GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	// ================================================================================================================
    // WRAPING SETTINGS

	unsigned int wrappingSettings = 0;

	switch (m_wrapingMode)
	{							   
	case Wraping::Repeat:          wrappingSettings = GL_REPEAT;            break;
	case Wraping::ClampToEdge:     wrappingSettings = GL_CLAMP_TO_EDGE;     break;
	case Wraping::ClampToBorder:   wrappingSettings = GL_CLAMP_TO_BORDER;   break;
	case Wraping::MirroredRepeat:  wrappingSettings = GL_MIRRORED_REPEAT;   break;
	}

	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingSettings));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingSettings));

	// ================================================================================================================
	// FILTERING SETTINGS
	unsigned int filteringSettingsMag = 0;
	unsigned int filteringSettingsMin = 0;
	bool useMipMap = false;
	switch (m_filteringMode)
	{
	case Filtering::Linear:              filteringSettingsMag = GL_LINEAR;  filteringSettingsMin = GL_LINEAR; break;
	case Filtering::Nearest:             filteringSettingsMag = GL_NEAREST; filteringSettingsMin = GL_NEAREST; break;
	case Filtering::Linear_MIP_Linear:   filteringSettingsMag = GL_LINEAR;  filteringSettingsMin = GL_LINEAR_MIPMAP_LINEAR;   useMipMap = true; break;
	case Filtering::Linear_MIP_Nearest:  filteringSettingsMag = GL_LINEAR;  filteringSettingsMin = GL_LINEAR_MIPMAP_NEAREST;  useMipMap = true; break;
	case Filtering::Nearest_MIP_Linear:  filteringSettingsMag = GL_NEAREST; filteringSettingsMin = GL_NEAREST_MIPMAP_LINEAR;  useMipMap = true; break;
	case Filtering::Nearest_MIP_Nearest: filteringSettingsMag = GL_NEAREST; filteringSettingsMin = GL_NEAREST_MIPMAP_NEAREST; useMipMap = true; break;
	}
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filteringSettingsMin));
	GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filteringSettingsMag));

	glGenerateMipmap(GL_TEXTURE_2D);
}

unsigned int Texture::GetInternalFormat()
{
	// Abstract this later in a RHI call to make it API independent
	switch (m_format)
	{
	case Format::RGBA8: return GL_RGBA8;
	 default: return 0;
	}
}

unsigned int Texture::GetDataFormat()
{
	return GL_RGBA; // TO DO: Come up with an actual architecture for this. 
}
