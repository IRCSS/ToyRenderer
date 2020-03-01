#include "rendering/Material.h"

namespace ToyRenderer {
    Material::Material()
	{

	}
	Material::Material(Shader * shader) : m_Shader(shader)
	{

	}
	void Material::SetInt(const std::string & name, int i)
	{
		m_pIntegers[name] = i;

	}
	void Material::SetFloat(const std::string & name, float f)
	{
		m_pFloats[name] = f;
	}
	void Material::SetTexture(const std::string & name, const Texture * t)
	{
		m_pTextures[name] = t;
	}
	void Material::SetColor(const std::string & name, Color c)
	{
		m_pColors[name] = c;
	}
	void Material::SetMatrix(const std::string & name, Matrix4x4 m)
	{
		m_pMatrices[name] = m;
	}
}
