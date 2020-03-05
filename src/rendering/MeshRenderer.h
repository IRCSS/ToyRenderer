#pragma once
#include "rendering/Material.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "rendering/Mesh/Mesh.h"
namespace ToyRenderer {

	class MeshRenderer {

	public:
    //  -------------------   ------------------
		Material*             material;
		Shader*               shader;

		VertexBuffer*         vertexBuffer;
		IndexBuffer *         indexBuffer;

		VertexBufferLayout*   vertexBufferLayout;

	private:
		Mesh* mesh;

	public: 
		MeshRenderer();
	   ~MeshRenderer();

	   MeshRenderer(Mesh* m);

	};

}