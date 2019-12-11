#include "IndexBuffer.h" 
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int * data, unsigned int count) : m_Count(count)
{
	Assert(sizeof(unsigned int) == sizeof(GLuint));

	GlCall(glGenBuffers(1, &m_RendererID));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

}

IndexBuffer::~IndexBuffer()
{
	GlCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
