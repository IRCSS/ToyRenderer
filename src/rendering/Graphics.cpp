#include "Graphics.h"
#include "rendering/MeshRenderer.h"
#include "rendering/Material.h"
#include "rendering/Mesh/Mesh.h"
namespace ToyRenderer {
	namespace Rendering {
		Graphic::Graphic()
		{
			Mesh* fullScreenQuadMesh = new Mesh();

		}
		Graphic::~Graphic()
		{
			delete m_defaultMaterial;
			delete m_fullScreenQuad;
		}
	}
}



