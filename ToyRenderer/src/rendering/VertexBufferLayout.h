#pragma once
#include "Core.h"
#include "vendor/GL/glew.h"
#include <vector>
#include "rendering/Renderer.h"
namespace ToyRenderer{
    struct TOYRENDERER_API VertexBufferElement {
    	unsigned int type;             // Vertex Buffer Element Type. Using OpenGl enums for now. Later will make them more generalized
    	unsigned int count;            // Number of entries for this element. For example layout can be 1 float, 2 int, 1 float. For the int entry you would have type GL_UNSIGNED_INT and count 2
    	unsigned char normalized;      // if the value is normalized between 0-1 openGl needs this specification. 
    	// To DO: Add semantics. Best would be a header file with enum values as ints and a parser. The semantics would be the standard HLSL ones such as: 
    	// TEXCOORD## (1 to 9)
    	// NORMAL
    	// BINORMAL
    	// TANGENT
    	// POSITION
    	// COLOR and other SV semntics for instanscing 
    
    	static unsigned int GetSizeOfType(unsigned int type) {
    		switch (type)
    		{
    		case GL_FLOAT:           return 4;
    		case GL_UNSIGNED_INT:    return 4;
    		case GL_UNSIGNED_BYTE:   return 1;
    		}
    
    		Assert(false);
    		return 0;
    	}
    
    };
    
    class TOYRENDERER_API VertexBufferLayout {
	// PUBLIC ======================================================================================
    public:
    	VertexBufferLayout() : m_Stride(0) {};
    
    
    	// No real reason why this is templated. Could have also been a normal function_type series. The difference here is that the program can still push in 
    	// unsoppurted type, the program would just crash. This can be changed later to runtime errors. 
    	template<typename T>
    	void Push(unsigned int count) {
    		static_assert(false);
    	}
    
    	template<>
    	void Push<float>(unsigned int count) {
    		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);;
    	}
    
    
    	template<>
    	void Push<unsigned int>(unsigned int count) {
    		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    	}
    
    	template<>
    	void Push<unsigned char>(unsigned int count) {
    		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);;
    	}
    
    
    	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
    	inline unsigned int GetStride() const{ return m_Stride; }
	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
    #pragma warning( disable : 4251)  
    // std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. Private stuff wont be inlined so I will disable them

    private: 
    	std::vector<VertexBufferElement> m_Elements;
    	unsigned int m_Stride; 
    #pragma warning(default:4251) // Turning the 4251 back on

    };
}