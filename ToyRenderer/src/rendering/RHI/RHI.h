#pragma once
#include "Core.h"
#include <string>
#include "rendering/RHI/RenderingSettingTypes.h"
#include "rendering/RHI/RenderingPipelineTypes.h"
// To Do Implement Later
namespace ToyRenderer {
	namespace Rendering {

		static class TOYRENDERER_API RHI {
	    
		// PUBLIC ======================================================================================

		public: // TYPES

			enum Material_DepthFunction{ ALWAYS, NEVER, LESS, EQUAL, LEQUAL, GREATER,NOTEQUAL, GEQUAL};


		public:

			static void BindBackBuffer();

			static void BeginMarkerGroup( const std::string& markerName);
			static void EndMarkerGroup();


			static void EnableBackFaceCulling (const bool enable);
			static void EnableZTest           (const bool enable);
			static void EnableDepthBufferWrite(const bool enable);
            static void EnableBlend           (const bool enable);
			static void SetDepthFucntion      (const Material_DepthFunction depthFunction);
			static void SetBlendFunction      (const Blend_Function src, const Blend_Function dst);



			// SHADERS

			static unsigned int   CreateProgram       ();
			static void           DeleteProgram       (unsigned int programID);
			static void           SetProgramActive    (unsigned int programID);
			static unsigned int   CreateShader        (ShaderTypes  shaderType);
			static void           SetShaderSource     (unsigned int shaderID, const char* shaderSource, int* length = nullptr);
			static void           CompileShader       (unsigned int shaderID);
			static void  CheckCompilationShaderStatus (unsigned int shaderID, ShaderTypes type);
			
			static void           AttachShader        (unsigned int ProgramID, unsigned int ShaderID);
			static void           LinkProgram         (unsigned int ProgramID);
			static void           ValidateProgram     (unsigned int ProgramID);
			static void           DeleteShader        (unsigned int ShaderID);


			static void SetUniformFloat4    (int location, float v0, float v1, float v2, float v3);
			static void SetUniformFloat     (int location, float v0);
			static void SetUniformInteger   (int location, int v0);
			static void SetUniformMatrix4F  (int location, const float* matrixAddress);
			static int  GetUniformLocation  (unsigned int programID, const char* uniformName);



		};

	}
}