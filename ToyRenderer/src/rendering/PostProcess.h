#pragma once
#include "Core.h"
namespace ToyRenderer {
    class Renderer;
	namespace Rendering {

		class FrameBuffer;
		class TOYRENDERER_API PostProcess {

		// PUBLIC ======================================================================================
		public:
			PostProcess() {};
			 virtual ~PostProcess() {};
			 virtual void OnPostRender(FrameBuffer& src, FrameBuffer& dst, Renderer& renderer) = 0;
			 
		};

	}
}