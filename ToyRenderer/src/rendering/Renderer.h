#pragma once
#include <vendor/GL/glew.h>
#define Assert(x) if(!(x)) __debugbreak();
#define GlCall(x) GLClearError();        \
                  x;                   \
                  Assert(GLCheckError(#x, __FILE__, __LINE__)) \
// To Do: figure out a way to make sure that if GlCall is places in a scope or if or ... that things still work out 


void GLClearError();
bool GLCheckError(const char* functionName, const char* fileName, const int line);

#include "rendering/Graphics.h"

class VertexArray;
class IndexBuffer;
class Shader;
namespace ToyRenderer {
	class Color;

}

class Renderer {

private: 
	ToyRenderer::Rendering::Graphic m_graphicUtility;
public:
	Renderer();
	
	void Clear(ToyRenderer::Color clearColor, float depthClearValue, bool clearDepth) const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

};