#pragma once
#include "Core.h"
#include "rendering/Texture.h"
#include "rendering/RenderBuffer.h"

namespace ToyRenderer {

	namespace Rendering {

		class TOYRENDERER_API FrameBuffer {
		
		// PUBLIC ======================================================================================
		public:

			//Delete the copy constructor/assignment for All OpenGl Resources to avoid deleting reosurce on GPU on move/ coppy
			FrameBuffer(const FrameBuffer &)            = delete;
			FrameBuffer &operator=(const FrameBuffer &) = delete;

			FrameBuffer(unsigned int width, unsigned int height, Texture::Format colorBufferFormat, RenderBuffer::Format depthBufferFormat);
			~FrameBuffer();

			bool IsValid() const;
			void Bind()    const;
			void UnBind()  const;

			Texture* GetTexturePointer() const;
		public:
			unsigned int m_RendererID;
			
	    // ______________________________________________________________________________________________
	    // PRIVATE ======================================================================================
		private:
			Texture*      m_renderTexture;
			RenderBuffer* m_renderBuffer;

			unsigned int          m_width, m_heigth;
			Texture::Format       m_colorBufferFormat;
			RenderBuffer::Format  m_depthBufferFormat;


		};

	}
}
