#pragma once
#include "Core.h"
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

#define Material_PASS_OPAQUE      0
#define Material_PASS_SKYBOX      1
#define Material_PASS_TRANSPARENT 2

namespace ToyRenderer {
    class Shader;
	
	class TOYRENDERER_API Material {
	// PUBLIC ======================================================================================
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

		void SetTwoSided   (const bool TwoSided);
		void EnableZTest   (const bool enabled);
		void EnableZWrite  (const bool enabled);
		void EnableBlend   (const bool enabled);

		/// use Material_DepthFunction macro
		void SetDepthFunction(const int  mode);

		/// use Material_Pass macro
		void SetRenderPass(const int passID);
		int  GetPass();

	public:
		int     m_AssetID;
		Shader* m_Shader;
	
	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private:

		void InitializeSettingsValues();

    #pragma warning( disable : 4251)  
    // std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. Private stuff wont be inlined so I will disable them

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
		int  settings_renderPass;

    #pragma warning(default:4251) // Turning the 4251 back on
	};
}