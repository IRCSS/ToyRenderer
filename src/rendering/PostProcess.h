#pragma once
namespace ToyRenderer {
	namespace Rendering {

		class FrameBuffer;
		class PostProcess {
		public:
			PostProcess() {};
			 virtual ~PostProcess() = 0;
			 virtual void OnPostRender(FrameBuffer& src, FrameBuffer& dst) = 0;
			 
		};

	}
}