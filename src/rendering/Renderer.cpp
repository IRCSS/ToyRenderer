#include "rendering/Renderer.h"
#include <iostream>
#include "log/Log.h"
#include "Graphics.h"
void GLClearError() {

	while (glGetError() != GL_NO_ERROR);
}
bool GLCheckError(const char* functionName, const char* fileName, const int line) {

	bool foundError = false;
	while (GLenum error = glGetError()) {
		ENGINE_LOG_ERROR("[OpenGl Error]: {}, In Function, {}, in file, {}: Line {}", error, functionName, fileName, line);  // to do: convert the error from hexa decimal, to int and from glew get the actual error name 
		foundError = true;

	}

	if (foundError) return false; // this is returned for the assert macro
	return true;
}

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "maths/Color.h"

Renderer::Renderer()
{
	ToyRenderer::Rendering::Graphic m_graphicUtility();
}

void Renderer::Clear(ToyRenderer::Color clearColor, float depthClearValue, bool clearDepth) const
{
	GlCall(glClearColor(clearColor.m_red, clearColor.m_green, clearColor.m_blue, clearColor.m_alpha));
	if (!clearDepth) { GlCall(glClear(GL_COLOR_BUFFER_BIT)); }
	else { 
		glClearDepth(depthClearValue);
		GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); 
	}
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GlCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
