#pragma once
class Renderer;
namespace ToyRenderer {
	namespace Rendering {

		class FrameBuffer;
		class PostProcess {
		public:
			PostProcess() {};
			virtual ~PostProcess() {};
			 virtual void OnPostRender(FrameBuffer& src, FrameBuffer& dst, Renderer& renderer) = 0;
			 
		};

	}
}