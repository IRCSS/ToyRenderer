#include "MeshRenderer.h"
#include "Shader.h"
#include "rendering/Renderer.h"
#include "world/GameObject.h"
#include "Components/Transform.h"
#include "Material.h"
namespace ToyRenderer {

	MeshRenderer::MeshRenderer()
	{
	}
	MeshRenderer::~MeshRenderer()
	{
		delete vertexBuffer;
		delete indexBuffer;
		delete vertexBufferLayout;
		delete vertexArray;
	}
	MeshRenderer::MeshRenderer(Mesh * m) : mesh(m)
	{
		ExtractRenderProxyFromMesh();
	}
	

	MeshRenderer::MeshRenderer(Mesh * m, Material* mat) : mesh(m), material(mat)
	{
		ExtractRenderProxyFromMesh();
	}
	void MeshRenderer::Render( Renderer& renderer, const Matrix4x4 & vp)
	{
		if (!material) return;

		Matrix4x4 mvp = vp;

		if (gameObject) {
			if (!transform) transform = gameObject->GetComponent<Transform>();
			if (transform) mvp = mvp * transform->localToWorld();
		}
		material->m_Shader->Bind();
		material->m_Shader->SetUniformMat4("u_MVP", mvp.GetGLM());
		material->BindMaterialParameters();

		renderer.Draw(*vertexArray, *indexBuffer, *material->m_Shader);
		
	}
	void MeshRenderer::ExtractRenderProxyFromMesh()
	{
		if (!mesh) return;

		int vertexSize = 0;
		if (mesh->VertexPositions.size() != 0)  vertexSize += 3;
		if (mesh->uv.size() != 0) vertexSize += 2;
		if (mesh->VertexNormals.size() != 0) vertexSize += 3;
		if (mesh->VertexColors.size() != 0) vertexSize += 3;


		std::vector<float> vertices;
		vertices.reserve(vertexSize *  mesh->GetVertexCount());

		for (int i = 0; i < mesh->GetVertexCount(); i++) {
			
			if (mesh->VertexPositions.size() != 0) {
				
				vertices.push_back(mesh->VertexPositions[i].x);
				vertices.push_back(mesh->VertexPositions[i].y);
				vertices.push_back(mesh->VertexPositions[i].z);
			}
			if (mesh->uv.size() != 0) {

				vertices.push_back(mesh->uv[i].x);
				vertices.push_back(mesh->uv[i].y);
			}
			if (mesh->VertexNormals.size() != 0) {

				vertices.push_back(mesh->VertexNormals[i].x);
				vertices.push_back(mesh->VertexNormals[i].y);
				vertices.push_back(mesh->VertexNormals[i].z);
			}
			if (mesh->VertexColors.size() != 0) {

				vertices.push_back(mesh->VertexColors[i].m_red);
				vertices.push_back(mesh->VertexColors[i].m_green);
				vertices.push_back(mesh->VertexColors[i].m_blue);
			}

			
		}
		vertexBuffer = new VertexBuffer(&vertices[0], vertices.size() * sizeof(float));
		indexBuffer = new IndexBuffer(&mesh->triangles[0], mesh->triangles.size());

		vertexBufferLayout = new VertexBufferLayout();

		if (mesh->VertexPositions.size() != 0) vertexBufferLayout->Push<float>(3);
		if (mesh->uv.size() != 0) vertexBufferLayout->Push<float>(2);
		if (mesh->VertexNormals.size() != 0) vertexBufferLayout->Push<float>(3);
		if (mesh->VertexColors.size() != 0) vertexBufferLayout->Push<float>(3);


		vertexArray = new VertexArray();
		vertexArray->AddBuffer(*vertexBuffer, *vertexBufferLayout);

	}
}

