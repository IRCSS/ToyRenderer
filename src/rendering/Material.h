#pragma once
#include <unordered_map>
#include "Texture.h"
#include "maths/Color.h"
#include "maths/Matrix4x4.h"


#define Material_DepthFunction_ALWAYS   0
#define Material_DepthFunction_NEVER    1
#define Material_DepthFunction_LESS     2
#define Material_DepthFunction_EQUAL    3
#define Material_DepthFunction_LEQUAL   4
#define Material_DepthFunction_GREATER  5
#define Material_DepthFunction_NOTEQUAL 6
#define Material_DepthFunction_GEQUAL   7



class Shader;
namespace ToyRenderer {
	class Material {

	public:
		int     m_AssetID;
		Shader* m_Shader;

	private:
		std::unordered_map<std::string,       int>         m_pIntegers;
		std::unordered_map<std::string,       float>       m_pFloats;
		std::unordered_map<std::string, const Texture*>    m_pTextures;
		std::unordered_map<std::string,       Color>       m_pColors;
		std::unordered_map<std::string,       Matrix4x4>   m_pMatrices;


		bool settings_BackFaceCulling;
		bool settings_ZTest;
		bool settings_ZWrite;
		bool settings_Blend;
		int  settings_depthFunction;


	public:



		Material();
		Material(Shader* shader);

		void SetInt     (const std::string& name,       int       i);
		void SetFloat   (const std::string& name,       float     f);
		void SetTexture (const std::string& name, const Texture*  t);
		void SetColor   (const std::string& name,       Color     c);
		void SetVector  (const std::string& name,       Vector4   v);
		void SetMatrix  (const std::string& name,       Matrix4x4 m);

		void BindMaterialParameters();

		void SetTwoSided     (const bool TwoSided);
		void EnableZTest     (const bool enabled);
		void EnableZWrite    (const bool enabled);
		void EnableBlend     (const bool enabled);

		/// use Material_DepthFunction macro
		void SetDepthFunction(const int  mode);

	private:

		void InitializeSettingsValues();

	};

}