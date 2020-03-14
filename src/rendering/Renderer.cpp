#include "rendering/Renderer.h"
#include <iostream>
void GLClearError() {

	while (glGetError() != GL_NO_ERROR);
}
bool GLCheckError(const char* functionName, const char* fileName, const int line) {

	bool foundError = false;
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGl Error]: " << error << " In Function, " << functionName
			<< " in file, " << fileName << ": Line " << line << std::endl;               // to do: convert the error from hexa decimal, to int and from glew get the actual error name 
		foundError = true;

	}

	if (foundError) return false; // this is returned for the assert macro
	return true;
}

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

void Renderer::Clear() const
{
	GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GlCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
