#include "MeshRenderer.h"

namespace ToyRenderer {
	MeshRenderer::MeshRenderer()
	{
	}
	MeshRenderer::~MeshRenderer()
	{
		delete vertexBuffer;
		delete indexBuffer;
		delete vertexBufferLayout;
	}
	MeshRenderer::MeshRenderer(Mesh * m)
	{
	}
}

