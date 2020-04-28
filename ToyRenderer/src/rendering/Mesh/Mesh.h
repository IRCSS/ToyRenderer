#pragma once
#include "Core.h"
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "maths/Vector2.h"
#include "rendering/Bounds.h"
#include <vector>
#include "maths/Color.h"
namespace ToyRenderer {

	class TOYRENDERER_API Mesh {
	// PUBLIC ======================================================================================
	public:
		Mesh();
		int GetVertexCount() const;

	public:

		Bounds                    AAB;
		std::vector<Color>        VertexColors;
		std::vector<Vector3>      VertexNormals;
		//std::vector<Vector3>    VertexTangents;
		std::vector<unsigned int> triangles;   // AKA index buffer
		std::vector<Vector3>      VertexPositions;
		std::vector<Vector2>      uv;
		
		int m_AssetID;

	};

}