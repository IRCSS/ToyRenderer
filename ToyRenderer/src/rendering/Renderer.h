#pragma once
#include "Core.h"
#include <vendor/GL/glew.h>
#include "rendering/Graphics.h"

#define Assert(x) if(!(x)) __debugbreak();
#define GlCall(x) GLClearError();        \
                  x;                   \
                  Assert(GLCheckError(#x, __FILE__, __LINE__)) \
// To Do: figure out a way to make sure that if GlCall is places in a scope or if or ... that things still work out 





namespace ToyRenderer {
	class Color;
    class VertexArray;
    class IndexBuffer;
    class Shader;

	TOYRENDERER_API void GLClearError();
	TOYRENDERER_API bool GLCheckError(const char* functionName, const char* fileName, const int line);

    class TOYRENDERER_API Renderer {
	// PUBLIC ======================================================================================
    public:
    	Renderer();
    	
    	void Clear(ToyRenderer::Color clearColor, float depthClearValue, bool clearDepth) const;
    	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	
	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
    private: 
    	Rendering::Graphic m_graphicUtility;
    
    };
}