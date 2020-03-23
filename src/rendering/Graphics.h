#pragma once
namespace ToyRenderer {
	class MeshRenderer;
	namespace Rendering {
		class FrameBuffer;
		class Graphic {

		private: 
			static MeshRenderer* fullScreenQuad;

		public:

			// Graphics
			static void Blit(const FrameBuffer& src, const FrameBuffer& dst);
		};
	}
}