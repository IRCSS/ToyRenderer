#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture()
{
	GlCall(glGenTextures(1, &m_RendererID));
	GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
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
	
	GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
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
