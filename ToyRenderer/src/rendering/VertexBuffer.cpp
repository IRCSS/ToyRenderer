#include "VertexBuffer.h" 
#include "rendering/Renderer.h"

VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	GlCall(glGenBuffers(1, &m_RendererID));
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GlCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind()const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
