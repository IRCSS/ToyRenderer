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
class Renderer;

namespace ToyRenderer {

	class Material;
	class Transform;
	class MeshRenderer : public Component{

	public:
    //  -------------------   ------------------
		Material*             material;

		VertexBuffer*         vertexBuffer;
		IndexBuffer *         indexBuffer;
		VertexArray *         vertexArray;

		VertexBufferLayout*   vertexBufferLayout;

	private:
		Mesh*      mesh;
		Transform* transform;

	public: 
		MeshRenderer();
	   ~MeshRenderer();

	   MeshRenderer(Mesh* m);
	   MeshRenderer(Mesh* mesh, Material* material);

	   void Render( Renderer& renderer, const Matrix4x4& vp);
	   /// Renderwithout camera MVP matrix. 
	   void Render( Renderer& renderer); 
   private:
	   void ExtractRenderProxyFromMesh();


	};

}