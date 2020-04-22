#include "rendering/Mesh/Mesh.h"

namespace ToyRenderer {
    Mesh::Mesh()
	{
	}
	int Mesh::GetVertexCount() const
	{
		return VertexPositions.size();

	}
}

