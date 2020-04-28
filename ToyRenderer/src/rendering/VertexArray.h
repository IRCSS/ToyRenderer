#pragma once
#include "Core.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace ToyRenderer{
    class TOYRENDERER_API VertexArray
    {
	// PUBLIC ======================================================================================
    public: 
    	VertexArray();
       ~VertexArray();
        
       //Delete the copy constructor/assignment for All OpenGl Resources to avoid deleting reosurce on GPU on move/ coppy
       VertexArray(const VertexArray&) = delete;
       VertexArray &operator=(const VertexArray&) = delete;
       
       void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout layout);
       void Bind() const;
       void UnBind() const;
	// ______________________________________________________________________________________________
    // PRIVATE ======================================================================================
    private: 
    	unsigned int m_RendererID;    // holds the actual ID int of the vertex array. This is not a pointer to the int. 
    
    };
}