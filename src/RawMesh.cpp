#include "RawMesh.h"

namespace ToyRenderer {
	t_RawMeshSubShape::t_RawMeshSubShape(int fCount) : faceCount(fCount)
	{

	}
	t_RawMeshIndices::t_RawMeshIndices(int vp_index, int n_index, int texc_index) : position_index(vp_index), normal_index(n_index), texcoord_index(texc_index)
	{
	}
}



