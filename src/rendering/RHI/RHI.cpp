#include "RHI.h"
#include "rendering/Renderer.h"
namespace ToyRenderer {
	namespace Rendering {
          void ToyRenderer::Rendering::RHI::BindBackBuffer()
          {
			  GlCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
          }

	}
}
