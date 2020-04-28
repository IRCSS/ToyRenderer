#pragma once
#include "Core.h"
#include "rendering/Material.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "rendering/Mesh/Mesh.h"
#include "VertexArray.h"
#include "Components/Component.h"

namespace ToyRenderer {

    class Matrix4x4;
    class Renderer;
	class Material;
	class Transform;
	class TOYRENDERER_API MeshRenderer : public Component{

	// PUBLIC ======================================================================================
	public: 
		MeshRenderer();
	   ~MeshRenderer();

	   MeshRenderer(Mesh* m);
	   MeshRenderer(Mesh* mesh, Material* material);

	   void Render( Renderer& renderer, const Matrix4x4& vp);
	   /// Renderwithout camera MVP matrix. 
	   void Render( Renderer& renderer); 
	public:
    //  -------------------   ------------------
		Material*             material;

		VertexBuffer*         vertexBuffer;
		IndexBuffer *         indexBuffer;
		VertexArray *         vertexArray;

		VertexBufferLayout*   vertexBufferLayout;
	
	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
   
	private:
	   void ExtractRenderProxyFromMesh();

	private:
		Mesh*      mesh;
		Transform* transform;

	};

}