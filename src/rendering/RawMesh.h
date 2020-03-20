#pragma once
#include "maths/Vector2.h"
#include "maths/Vector3.h"
#include "maths/Vector4.h"
#include <vector>
#include "rendering/Mesh/Mesh.h"
#include "maths/Color.h"
#include "rendering/Material.h"


namespace ToyRenderer {

	struct t_RawMeshIndices {
		
	public:
		int position_index;
		int normal_index;
		int texcoord_index;
		int color_index;

		t_RawMeshIndices(int vp_index, int vn_index, int texc_index, int color_index);
		t_RawMeshIndices();
	};

	struct t_RawMeshSubShape {
	public:
		std::vector<t_RawMeshIndices>   m_facesIndices;
		std::vector<int>                m_FaceMaterialIndex;
		int faceCount;
		t_RawMeshSubShape(int faceCount);
		t_RawMeshSubShape();
	};

	class RawMesh {

	public: 
		
		std::vector<Color>              m_VertexColors;
		std::vector<Vector3>            m_VertexPositions;
		std::vector<Vector3>            m_VertexNormals;
		std::vector<Vector2>            m_uv;
		std::vector<t_RawMeshSubShape>  m_subShapes; // an array of faces which is an array of indices. A face can be a series of different indices, each index hold index in vColors, vPosition and vNormals array. 
		std::vector<Material*>          m_materials;
		std::vector<Mesh*>              m_meshes;
		std::vector<int>                m_meshes_materials_ids;
		int                m_subShapesCount;

	private:

	public:
		RawMesh();


		const std::vector<Mesh*>& GenerateMeshes();
    

	private:

	};

}