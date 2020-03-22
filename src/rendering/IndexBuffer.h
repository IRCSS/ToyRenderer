#pragma once

class IndexBuffer {
private: 
	unsigned int m_RendererID;
	unsigned int m_Count;
public: 
	IndexBuffer(const unsigned int* data, unsigned int count);
   ~IndexBuffer();

   //Delete the copy constructor/assignment for All OpenGl Resources to avoid deleting reosurce on GPU on move/ coppy
   IndexBuffer(const IndexBuffer &) = delete;
   IndexBuffer &operator=(const IndexBuffer &) = delete;

   void Bind() const;
   void UnBind() const;

   inline unsigned int GetCount() const { return m_Count; }
};
