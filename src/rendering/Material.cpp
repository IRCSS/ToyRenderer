#include "rendering/Material.h"
#include "Shader.h"
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
	void Material::BindMaterialParameters()
	{
		auto it_matrix = m_pMatrices.begin();
		while (it_matrix != m_pMatrices.end()) {

			m_Shader->SetUniformMat4(it_matrix->first, it_matrix->second.GetGLM());
			it_matrix++;
		}

		auto it_Float = m_pFloats.begin();
		while (it_Float != m_pFloats.end()) {

			m_Shader->SetUniformf(it_Float->first, it_Float->second);
			it_Float++;
		}

		auto it_Int = m_pIntegers.begin();
		while (it_Int != m_pIntegers.end()) {

			m_Shader->SetUniform1i(it_Int->first, it_Int->second);
			it_Int++;
		}

		auto it_Color = m_pColors.begin();
		while (it_Color != m_pColors.end()) {

			m_Shader->SetUniform4f(it_Color->first, it_Color->second.m_red, it_Color->second.m_green, it_Color->second.m_blue, 1.0f);
			it_Color++;
		}

		int numberOfTextures = 0;

		auto it_Textures = m_pTextures.begin();
		while (it_Textures != m_pTextures.end()) {

			if (numberOfTextures >= 31) break;
			m_Shader->SetUniform1i(it_Textures->first, numberOfTextures);
			it_Textures->second->Bind();
			numberOfTextures++;

			it_Textures++;
		}

		

	}
}
