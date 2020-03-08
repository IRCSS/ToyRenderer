#pragma once
#include "rendering/Material.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "rendering/Mesh/Mesh.h"
#include "VertexArray.h"
#include "Components/Component.h"

class Matrix4x4;

namespace ToyRenderer {

	class MeshRenderer : public Component{

	public:
    //  -------------------   ------------------
		Material*             material;
		Shader*               shader;

		VertexBuffer*         vertexBuffer;
		IndexBuffer *         indexBuffer;
		VertexArray *         vertexArray;

		VertexBufferLayout*   vertexBufferLayout;

	private:
		Mesh* mesh;

	public: 
		MeshRenderer();
	   ~MeshRenderer();

	   MeshRenderer(Mesh* m);
	   MeshRenderer(Mesh* m, Shader* s);

	   void Render(const Matrix4x4& vp);

   private:
	   void ExtractRenderProxyFromMesh();


	};

}