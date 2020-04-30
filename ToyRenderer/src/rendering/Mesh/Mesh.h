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
    #pragma warning( disable : 4251)  
    // std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. 
	public:

		Bounds                    AAB;
		std::vector<Color>        VertexColors;
		std::vector<Vector3>      VertexNormals;
		//std::vector<Vector3>    VertexTangents;
		std::vector<unsigned int> triangles;   // AKA index buffer
		std::vector<Vector3>      VertexPositions;
		std::vector<Vector2>      uv;
		
		int m_AssetID;
    #pragma warning(default:4251) // Turning the 4251 back on
	};

}