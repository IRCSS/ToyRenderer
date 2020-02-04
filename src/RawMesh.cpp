#include "RawMesh.h"

namespace ToyRenderer {
	t_RawMeshSubShape::t_RawMeshSubShape(int fCount) : faceCount(fCount)
	{

	}
	t_RawMeshSubShape::t_RawMeshSubShape() : faceCount(0)
	{
	}
	t_RawMeshIndices::t_RawMeshIndices(int vp_index, int n_index, int texc_index) : position_index(vp_index), normal_index(n_index), texcoord_index(texc_index)
	{
	}
	t_RawMeshIndices::t_RawMeshIndices() : position_index(0), normal_index(0), texcoord_index(0)
	{
	}
	RawMesh::RawMesh() : m_subShapes(0)
	{
	}



	const std::vector<Mesh>& RawMesh::GenerateMeshes() const
	{
		if (m_subShapesCount == 0) return std::vector<Mesh>();
		
		for (int i = 0; i < m_subShapes.size(); i++) {




		}

		return std::vector<Mesh>();
	}
}



