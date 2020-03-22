#pragma once
#include "rendering/Texture.h"
#include "rendering/RenderBuffer.h"

namespace ToyRenderer {

	namespace Rendering {

		class FrameBuffer {
		public:
			unsigned int m_RendererID;
			
		private:
			Texture*      m_renderTexture;
			RenderBuffer* m_renderBuffer;

		public:


			//Delete the copy constructor/assignment for All OpenGl Resources to avoid deleting reosurce on GPU on move/ coppy
			FrameBuffer(const FrameBuffer &)            = delete;
			FrameBuffer &operator=(const FrameBuffer &) = delete;


			void Bind()   const;
			void UnBind() const;

		};

	}
}
