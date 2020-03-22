#include "FrameBuffer.h"

namespace ToyRenderer {
	namespace Rendering {
		FrameBuffer::FrameBuffer(unsigned int width, unsigned int height, Texture::Format colorBufferFormat, RenderBuffer::Format depthBufferFormat) :
			m_width(width), m_heigth(height), m_colorBufferFormat(colorBufferFormat), m_depthBufferFormat(depthBufferFormat) , m_renderTexture(nullptr),
			m_renderBuffer(nullptr)
		{
			GlCall(glGenFramebuffers(1, &m_RendererID));
			Bind();

			// Create Texture for the color buffer
			m_renderTexture = new Texture     (m_width, m_heigth, Texture::Filtering::Nearest, Texture::Wraping::ClampToEdge, colorBufferFormat);
			m_renderBuffer  = new RenderBuffer(m_width, m_heigth, RenderBuffer::Format::Depth_24);


			// Bind Color and deppth to fraebuffer

			// Set "renderedTexture" as our colour attachement #0
			GlCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_renderTexture->GetRenderID(), 0));

			// Set the list of draw buffers.
			GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
			GlCall(glDrawBuffers(1, DrawBuffers)); // "1" is the size of DrawBuffers

			// For Deferred, above needs to look different

			GlCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_renderBuffer->GetRendererID()));



		}
		FrameBuffer::~FrameBuffer()
		{
			delete m_renderTexture;
			delete m_renderBuffer;
			GlCall(glDeleteFramebuffers(1, &m_RendererID));
		}
		bool FrameBuffer::IsValid() const
		{
			Bind();
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				return false;
			return true;
		}
		void FrameBuffer::Bind() const
		{
			GlCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
		}
		void FrameBuffer::UnBind() const
		{
			GlCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}
	}
}

