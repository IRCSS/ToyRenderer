#include "rendering/Material.h"
#include "Shader.h"
namespace ToyRenderer {


    Material::Material()
	{

	}
	Material::Material(Shader * shader) : m_Shader(shader)
	{
		InitializeSettingsValues();

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
	void Material::SetVector(const std::string & name, Vector4 v)
	{
		m_pColors[name] = Color(v.x, v.y, v.z, v.w);
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

			m_Shader->SetUniform4f(it_Color->first, it_Color->second.m_red, it_Color->second.m_green, it_Color->second.m_blue, it_Color->second.m_alpha);
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


		if (settings_BackFaceCulling) glEnable(GL_CULL_FACE);
		else glDisable(GL_CULL_FACE);

		if (settings_ZTest) glEnable(GL_DEPTH_TEST);
		else glDisable(GL_DEPTH_TEST);

		if (settings_ZWrite) glDepthMask(GL_TRUE);
		else glDepthMask(GL_FALSE);

		if (settings_Blend) glEnable(GL_BLEND);
		else glDisable(GL_BLEND);
	
		switch (settings_depthFunction) {
		case Material_DepthFunction_ALWAYS:   glDepthFunc(GL_ALWAYS);   break;
		case Material_DepthFunction_EQUAL:    glDepthFunc(GL_EQUAL);    break;
		case Material_DepthFunction_GEQUAL:   glDepthFunc(GL_GEQUAL);   break;
		case Material_DepthFunction_GREATER:  glDepthFunc(GL_GREATER);  break;
		case Material_DepthFunction_LEQUAL:   glDepthFunc(GL_LEQUAL);   break;
		case Material_DepthFunction_LESS:     glDepthFunc(GL_LESS);     break;
		case Material_DepthFunction_NEVER:    glDepthFunc(GL_NEVER);    break;
		case Material_DepthFunction_NOTEQUAL: glDepthFunc(GL_NOTEQUAL); break;
		}
	}
	void Material::SetTwoSided(const bool TwoSided)
	{
		settings_BackFaceCulling = !TwoSided;
	}
	void Material::EnableZTest(const bool enabled)
	{
		settings_ZTest  = enabled;
	}
	void Material::EnableZWrite(const bool enabled)
	{
		settings_ZWrite = enabled;
	}
	void Material::EnableBlend(const bool enabled)
	{
		settings_Blend  = enabled;
	}
	void Material::SetDepthFunction(const int mode)
	{
		settings_depthFunction = mode;
	}
	void Material::InitializeSettingsValues()
	{
		settings_BackFaceCulling = true;
		settings_ZTest           = true;
	    settings_ZWrite          = true;
	    settings_Blend           = false;
		settings_depthFunction   = Material_DepthFunction_LESS;
	}

}
