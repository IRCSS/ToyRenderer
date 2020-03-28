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


	}
}
