#include "RHI.h"
#include "rendering/Renderer.h"
#include "log/Log.h"

namespace ToyRenderer {
	namespace Rendering {
          void ToyRenderer::Rendering::RHI::BindBackBuffer()
          {
			  GlCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
          }
		  void RHI::BeginMarkerGroup( const std::string& marker)
		  {
			  GlCall(glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, marker.c_str()));
		  }

		  void RHI::EndMarkerGroup()
		  {
			  GlCall(glPopDebugGroup());
		  }

		  void RHI::EnableBackFaceCulling(const bool enable)
		  {
			  if (enable) { GlCall(glEnable(GL_CULL_FACE)); }
			  else {GlCall(glDisable(GL_CULL_FACE))};
		  }

		  void RHI::EnableZTest(const bool enable)
		  {
			  if (enable) { GlCall(glEnable(GL_DEPTH_TEST)); }
			  else {GlCall(glDisable(GL_DEPTH_TEST));}
		  }

		  void RHI::EnableDepthBufferWrite(const bool enable)
		  {
			  GlCall(glDepthMask(enable ? GL_TRUE : GL_FALSE));
		  }

		  void RHI::EnableBlend(const bool enable)
		  {
			  if (enable) { GlCall(glEnable(GL_BLEND)); }
			  else {GlCall(glDisable(GL_BLEND));}
		  }

		  void RHI::SetDepthFucntion(const Material_DepthFunction depthFunction)
		  {
			  switch (depthFunction) {
			  case Material_DepthFunction::ALWAYS:   glDepthFunc(GL_ALWAYS);   break;
			  case Material_DepthFunction::EQUAL:    glDepthFunc(GL_EQUAL);    break;
			  case Material_DepthFunction::GEQUAL:   glDepthFunc(GL_GEQUAL);   break;
			  case Material_DepthFunction::GREATER:  glDepthFunc(GL_GREATER);  break;
			  case Material_DepthFunction::LEQUAL:   glDepthFunc(GL_LEQUAL);   break;
			  case Material_DepthFunction::LESS:     glDepthFunc(GL_LESS);     break;
			  case Material_DepthFunction::NEVER:    glDepthFunc(GL_NEVER);    break;
			  case Material_DepthFunction::NOTEQUAL: glDepthFunc(GL_NOTEQUAL); break;
			  }
		  }

		  GLenum RHIBlendToGLBlend(const Blend_Function toCast) {
			  switch (toCast) {
			  case Blend_Function::ZERO:                     return GL_ZERO; 
			  case Blend_Function::ONE:                      return GL_ONE;
			  case Blend_Function::SRC_COLOR:                return GL_SRC_COLOR;
			  case Blend_Function::ONE_MINUS_SRC_COLOR:      return GL_ONE_MINUS_SRC_COLOR;
			  case Blend_Function::DST_COLOR:                return GL_DST_COLOR;
			  case Blend_Function::ONE_MINUS_DST_COLOR:      return GL_ONE_MINUS_DST_COLOR;
			  case Blend_Function::SRC_ALPHA:                return GL_SRC_ALPHA;
			  case Blend_Function::ONE_MINUS_SRC_ALPHA:      return GL_ONE_MINUS_SRC_ALPHA;
			  case Blend_Function::DST_ALPHA:                return GL_DST_ALPHA;
			  case Blend_Function::ONE_MINUS_DST_ALPHA:      return GL_ONE_MINUS_DST_ALPHA;
			  case Blend_Function::CONSTANT_COLOR:           return GL_CONSTANT_COLOR;
			  case Blend_Function::ONE_MINUS_CONSTANT_COLOR: return GL_ONE_MINUS_CONSTANT_COLOR;
			  case Blend_Function::CONSTANT_ALPHA:           return GL_CONSTANT_ALPHA;
			  case Blend_Function::ONE_MINUS_CONSTANT_ALPHA: return GL_ONE_MINUS_CONSTANT_ALPHA;
			  case Blend_Function::SRC_ALPHA_SATURATE:       return GL_SRC_ALPHA_SATURATE;
			  case Blend_Function::SRC1_COLOR:               return GL_SRC1_COLOR;
			  case Blend_Function::ONE_MINUS_SRC1_COLOR:     return GL_ONE_MINUS_SRC1_COLOR;
			  case Blend_Function::SRC1_ALPHA:               return GL_SRC1_ALPHA;
			  case Blend_Function::ONE_MINUS_SRC1_ALPHA:     return GL_ONE_MINUS_SRC1_ALPHA;
			  default: return GL_ZERO;
			  }
		  }

		  void RHI::SetBlendFunction(const Blend_Function src, const Blend_Function dst)
		  {
			  GlCall(glBlendFunc(RHIBlendToGLBlend(src), RHIBlendToGLBlend(dst)));
		  }


		  unsigned int RHI::CreateProgram()
		  {
			 GlCall(unsigned int programID = glCreateProgram());
			  return programID;
		  }

		  void RHI::DeleteProgram(unsigned int programID)
		  {
			  GlCall(glDeleteProgram(programID));
		  }

		  void RHI::SetProgramActive(unsigned int programID)
		  {
			  GlCall(glUseProgram(programID));
		  }

		  GLenum RHIShaderTypeToGLShaderType(ShaderTypes shaderType) {

				  switch(shaderType){
				  case ShaderTypes::COMPUTE_SHADER:         return GL_COMPUTE_SHADER;
				  case ShaderTypes::VERTEX_SHADER:          return GL_VERTEX_SHADER;
				  case ShaderTypes::TESS_CONTROL_SHADER:    return GL_TESS_CONTROL_SHADER;
				  case ShaderTypes::TESS_EVALUATION_SHADER: return GL_TESS_EVALUATION_SHADER;
				  case ShaderTypes::GEOMETRY_SHADER:        return GL_GEOMETRY_SHADER;
				  case ShaderTypes::FRAGMENT_SHADER:        return GL_FRAGMENT_SHADER;
		  };
		  }

		  unsigned int RHI::CreateShader(ShaderTypes shaderType)
		  {
			  GlCall(unsigned int id = glCreateShader(RHIShaderTypeToGLShaderType(shaderType)));
			  return id;
		  }

		  void RHI::SetShaderSource(unsigned int shaderID, const char * shaderSource, int * length)
		  {
			  GlCall(glShaderSource(shaderID, 1, &shaderSource, length));
		  }

		  void RHI::CompileShader(unsigned int shaderID)
		  {
			  GlCall(glCompileShader(shaderID));
		  }

		  void RHI::CheckCompilationShaderStatus(unsigned int shaderID, ShaderTypes type)
		  {
			  int result;
			  GlCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result));
			  if (result == GL_FALSE) {
				  int length;
				  GlCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length));
				  char* message = (char*)alloca(length * sizeof(char));
				  GlCall(glGetShaderInfoLog(shaderID, length, &length, message));

				  ENGINE_LOG_ERROR("RHI ERROR: Failed to compile {} shader! message: {}", (RHIShaderTypeToGLShaderType(type)== GL_VERTEX_SHADER ? "vertex " : "fragment "), message);

				  GlCall(glDeleteShader(shaderID));
			  }

		  }

		  void RHI::AttachShader(unsigned int ProgramID, unsigned int ShaderID)
		  {
			  GlCall(glAttachShader(ProgramID, ShaderID));
		  }

		  void RHI::LinkProgram(unsigned int ProgramID)
		  {
			  GlCall(glLinkProgram(ProgramID));
		  }

		  void RHI::ValidateProgram(unsigned int ProgramID)
		  {
			  GlCall(glValidateProgram(ProgramID));
		  }

		  void RHI::DeleteShader(unsigned int ShaderID)
		  {
			  GlCall(glDeleteShader(ShaderID));
		  }

		  void RHI::SetUniformFloat4(int location, float v0, float v1, float v2, float v3)
		  {
			  GlCall(glUniform4f(location, v0, v1, v2, v3));
		  }

		  void RHI::SetUniformFloat(int location, float v0)
		  {
			  GlCall(glUniform1f(location, v0));
		  }

		  void RHI::SetUniformInteger(int location, int v0)
		  {
			  GlCall(glUniform1i(location, v0));
		  }

		  void RHI::SetUniformMatrix4F(int location, const float * matrixAddress)
		  {
			  GlCall(glUniformMatrix4fv(location, 1, GL_FALSE, matrixAddress));
		  }

		  int RHI::GetUniformLocation(unsigned int programID, const char * uniformName)
		  {
			  GlCall(int location = glGetUniformLocation(programID, uniformName));
			  return location;
		  }

	}
}
