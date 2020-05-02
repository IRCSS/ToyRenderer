#include "rendering/Renderer.h"
#include <iostream>
#include "Graphics.h"
#include "rendering/IndexBuffer.h"
#include "log/Log.h"
#include "VertexArray.h"
#include "Shader.h"
#include "maths/Color.h"



namespace ToyRenderer{
   
	void GLClearError() {
    
    	while (glGetError() != GL_NO_ERROR);
    }
    
    const char* ParseGLError(GLenum error) {
    	switch (error) {
    	case GL_INVALID_ENUM:                  return "An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
    	case GL_INVALID_VALUE:                 return "A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
    	case GL_INVALID_OPERATION:             return "The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
    	case GL_INVALID_FRAMEBUFFER_OPERATION: return "The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.";
    	case GL_OUT_OF_MEMORY:                 return "There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
    	case GL_STACK_UNDERFLOW:               return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
    	case GL_STACK_OVERFLOW:                return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
    	default:                               return "unparsed Error";
    	}
    
    }
    
    bool GLCheckError(const char* functionName, const char* fileName, const int line) {
    
    	bool foundError = false;
    	while (GLenum error = glGetError()) {
    		ENGINE_LOG_ERROR("[OpenGl Error]: {}, {}, In Function, {}, in file, {}: Line {}", error, ParseGLError(error), functionName, fileName, line);  // to do: convert the error from hexa decimal, to int and from glew get the actual error name 
    		foundError = true;
    
    	}
    
    	if (foundError) return false; // this is returned for the assert macro
    	return true;
    }
    

    
    Renderer::Renderer() : m_graphicUtility(nullptr)
    {
    	m_graphicUtility = new Rendering::Graphic();
    }

	Renderer::~Renderer()
	{
		delete m_graphicUtility;
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
}