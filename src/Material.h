#pragma once
#include <unordered_map>
#include "Texture.h"
#include "Color.h"
#include "maths/Matrix4x4.h"
class Shader;
namespace ToyRenderer {
	class Material {

	public:


	private:
		std::unordered_map<std::string,       int>         m_pIntegers;
		std::unordered_map<std::string,       float>       m_pFloats;
		std::unordered_map<std::string, const Texture*>    m_pTextures;
		std::unordered_map<std::string,       Color>       m_pColors;
		std::unordered_map<std::string,       Matrix4x4>   m_pMatrices;
		
		Shader* m_Shader;


	public:

		Material();
		Material(Shader* shader);

		void SetInt     (const std::string& name,       int       i);
		void SetFloat   (const std::string& name,       float     f);
		void SetTexture (const std::string& name, const Texture*  t);
		void SetColor   (const std::string& name,       Color     c);
		void SetMatrix  (const std::string& name,       Matrix4x4 f);


	private:


	};

}