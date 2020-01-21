#pragma once
#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"
#include <vector>
#include "Mesh.h"
#include "Color.h"
#include "Material.h"

namespace ToyRenderer {

	class RawMesh {

	public: 
		
		std::vector<Color>              m_VertexColors;
		std::vector<Vector4>            m_VertexPositions;
		std::vector<Vector3>            m_VertexNormals;
		std::vector<Vector2>            m_uv;
		std::vector<std::vector<int>>   m_facesIndices; // an array of faces which is an array of indices. A face can be a series of different indices, each index hold index in vColors, vPosition and vNormals array. 
		std::vector<Material*>          m_materials;

		int                m_FaceCounts;
		int                m_subGroupsCount;

	private:

	public:
		RawMesh();


		std::vector<Mesh> GenerateMeshes() const;
    

	private:

	};

}