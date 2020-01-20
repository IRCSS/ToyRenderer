#pragma once
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "maths/Vector2.h"
#include "Bounds.h"


namespace ToyRenderer {

	class Mesh {

	public:
		Mesh();


	private:


	public:

		Bounds     m_AAB;
		Vector4*   m_VertexColors;
		Vector3*   m_VertexNormals;
		Vector3*   m_VertexTangents;
		int*       m_triangles;   // AKA index buffer
	    Vector4*   m_VertexPositions;
		int        m_VertexCount;
		Vector2*   m_uv;
		Vector2*   m_uv2;
	  //Material*  m_Material;


	};

}