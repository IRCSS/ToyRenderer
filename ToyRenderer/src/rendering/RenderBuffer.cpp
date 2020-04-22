#include "RenderBuffer.h"
#include "rendering/Renderer.h"

namespace ToyRenderer {
	namespace Rendering {
		RenderBuffer::RenderBuffer(unsigned int width, unsigned int heigth, const Format format) : m_RendererID(0), m_format(format), m_width(width),
			m_heigth(heigth)
		{
			GlCall(glGenRenderbuffers(1, &m_RendererID));
			Bind();
			GlCall(glRenderbufferStorage(GL_RENDERBUFFER, GetInternalFormat(), m_width, m_heigth));
			UnBind();

		}

		RenderBuffer::~RenderBuffer()
		{
			GlCall(glDeleteRenderbuffers(1, &m_RendererID));
		}

		void RenderBuffer::Bind() const
		{
			GlCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
		}

		void RenderBuffer::UnBind() const
		{
			GlCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
		}
		unsigned int RenderBuffer::GetRendererID() const
		{
			return m_RendererID;
		}
		unsigned int RenderBuffer::GetInternalFormat()
		{
			switch (m_format)
			{
			case Format::Depth_16:  return GL_DEPTH_COMPONENT16;
			case Format::Depth_24:  return GL_DEPTH_COMPONENT24;
			case Format::Depth_32:  return GL_DEPTH_COMPONENT32;
			case Format::RGBA:      return GL_RGBA;
			default: return GL_RGBA;
			}
		}
	}
}

