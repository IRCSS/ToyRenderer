#pragma once
#include <GL/glew.h>
#define Assert(x) if(!(x)) __debugbreak();
#define GlCall(x) GLClearError();        \
                  x;                   \
                  Assert(GLCheckError(#x, __FILE__, __LINE__)) \
// To Do: figure out a way to make sure that if GlCall is places in a scope or if or ... that things still work out 


void GLClearError();
bool GLCheckError(const char* functionName, const char* fileName, const int line);


class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {

private: 

public:

	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

};