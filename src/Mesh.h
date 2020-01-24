#pragma once
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "maths/Vector2.h"
#include "Bounds.h"


namespace ToyRenderer {

	class Mesh {

	public:

		Bounds   AAB;
		Vector4* VertexColors;
		Vector3* VertexNormals;
		Vector3* VertexTangents;
		int*     triangles;   // AKA index buffer
	    Vector4* VertexPositions;
		int      VertexCount;
		Vector2* uv;
		Vector2* uv2;
		int m_AssetID;

	private:


	public:
		Mesh();
		
		


	};

}