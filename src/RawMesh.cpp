#include "RawMesh.h"
#include "ResourceManager.h"
namespace ToyRenderer {
	t_RawMeshSubShape::t_RawMeshSubShape(int fCount) : faceCount(fCount)
	{

	}
	t_RawMeshSubShape::t_RawMeshSubShape() : faceCount(0)
	{
	}
	t_RawMeshIndices::t_RawMeshIndices(int vp_index, int vn_index, int texc_index, int vc_index) : position_index(vp_index), normal_index(n_index), texcoord_index(texc_index), color_index(vc_index)
	{
	}
	t_RawMeshIndices::t_RawMeshIndices() : position_index(0), normal_index(0), texcoord_index(0)
	{
	}
	RawMesh::RawMesh() : m_subShapes(0)
	{
	}



	const std::vector<Mesh*>& RawMesh::GenerateMeshes() const
	{
		std::vector<Mesh*> toReturn;
		if (m_subShapesCount == 0) return toReturn;
		


		for (int i = 0; i < m_subShapes.size(); i++) {

			std::unordered_map<int, Mesh*> parts;

			for (int j = 0; j < m_subShapes[i].faceCount; j++) {
				
				// -------------------------------------------------------------------------
				// Finding which mesh to write to, each mesh will be a drawcall. at the moment it is a mesh per subgroup per material.

				Mesh* meshToBuild;
				int materialID = m_subShapes[i].m_FaceMaterialIndex[j];
				if (parts.find(materialID) != parts.end()) meshToBuild =parts[materialID];
				else {
					meshToBuild = new Mesh();
					ResourceManager::Instance().RegisterMesh(meshToBuild);
					parts[materialID] = meshToBuild;
				}
				// -------------------------------------------------------------------------
				for (int k = 0; k < 3; k++) {   // At the moment only triangulated faces are suported, so each has only 3 
					int index = m_subShapes[i].m_facesIndices[j * 3 + k].position_index;
					meshToBuild->VertexPositions.push_back(m_VertexPositions[index]);

					    index = m_subShapes[i].m_facesIndices[j * 3 + k].normal_index;
					meshToBuild->VertexNormals.push_back(m_VertexNormals[index]);

					    index = m_subShapes[i].m_facesIndices[j * 3 + k].texcoord_index;
					meshToBuild->uv.push_back(m_uv[index]);

					    index = m_subShapes[i].m_facesIndices[j * 3 + k].position_index;
					meshToBuild->VertexColors.push_back(m_VertexColors[index]);

				}

			}

            std::unordered_map<int, Mesh*>::iterator it = parts.begin();

			// Iterate over the map using iterator
			while (it != parts.end())
			{
				toReturn.push_back(it->second);
				it++;
			}
			

		}

		return std::vector<Mesh*>();
	}
}



