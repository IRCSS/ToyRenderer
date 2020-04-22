#pragma once

class VertexBuffer {
private: 
	unsigned int m_RendererID;
public: 
	VertexBuffer(const void * data, unsigned int size);
   ~VertexBuffer();

   //Delete the copy constructor/assignment for All OpenGl Resources to avoid deleting reosurce on GPU on move/ coppy
   VertexBuffer(const VertexBuffer&) = delete;
   VertexBuffer &operator=(const VertexBuffer&) = delete;

   void Bind() const;
   void UnBind() const;
};
