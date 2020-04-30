#include "RHI.h"
#include "rendering/Renderer.h"
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


	}
}
