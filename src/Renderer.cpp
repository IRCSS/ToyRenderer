#include "Renderer.h"
#include <iostream>
void GLClearError() {

	while (glGetError() != GL_NO_ERROR);
}
bool GLCheckError(const char* functionName, const char* fileName, const int line) {

	bool foundError = false;
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGl Error]: " << error << " In Function, " << functionName
			<< " in file, " << fileName << ": Line " << line << std::endl;
		foundError = true;

	}

	if (foundError) return false;
	return true;
}