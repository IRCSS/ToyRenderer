#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{

	GlCall(glGenVertexArrays(1, &m_RendererID));

}

VertexArray::~VertexArray()
{
	GlCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer & vb, const VertexBufferLayout layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GlCall(glEnableVertexAttribArray(i));
		GlCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*) offset));
		offset += element.count * VertexBufferElements::GetSizeOfType(element.type);
	}



}

void VertexArray::Bind() const
{
	GlCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
	GlCall(glBindVertexArray(0));
}
