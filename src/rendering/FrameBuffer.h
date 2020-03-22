#pragma once
namespace ToyRenderer {
	namespace Rendering {

		class FrameBuffer {
		public:
			unsigned int m_RendererID;


		public:
			//Delete the copy constructor/assignment for All OpenGl Resources to avoid deleting reosurce on GPU on move/ coppy
			FrameBuffer(const FrameBuffer &) = delete;
			FrameBuffer &operator=(const FrameBuffer &) = delete;

		};

	}
}
