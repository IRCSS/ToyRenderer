#pragma once
#include <GL/glew.h>
#define Assert(x) if(!(x)) __debugbreak();
#define GlCall(x) GLClearError();        \
                  x;                   \
                  Assert(GLCheckError(#x, __FILE__, __LINE__)) \

void GLClearError();
bool GLCheckError(const char* functionName, const char* fileName, const int line);