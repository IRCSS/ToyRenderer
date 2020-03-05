#pragma once
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "maths/Vector2.h"
#include "Bounds.h"
#include <vector>
#include "maths/Color.h"
namespace ToyRenderer {

	class Mesh {

	public:

		Bounds   AAB;
		std::vector<Color>   VertexColors;
		std::vector<Vector3> VertexNormals;
		//std::vector<Vector3> VertexTangents;
		std::vector<unsigned int>     triangles;   // AKA index buffer
		std::vector<Vector3> VertexPositions;
		int      VertexCount;
		std::vector<Vector2> uv;
		
		int m_AssetID;

	private:


	public:
		Mesh();
		
		


	};

}