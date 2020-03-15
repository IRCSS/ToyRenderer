#include "ProceduralSkyBox.h"
#include "ResourceManager.h"
#include "Shader.h"

namespace ToyRenderer {
	

	ProceduralSkyBox::ProceduralSkyBox()
	{
		mesh = new Mesh();
		ResourceManager::Instance().RegisterMesh(mesh);

		PopulateVertexPosition();

		Shader* s = new Shader("res/shaders/procceduralSkybox.shader");
		Material* mat = new Material(s);
		ResourceManager::Instance().RegisterMaterial(mat);

		    TopColor = Color(0.368f, 0.776f, 0.929f);
		HorizonColor = Color(0.352f, 0.298f, 0.247f);
			SunDecay = Color(1.,0.95,0.9);
		   SunVector = Vector4(1.0f,-1.0f, 0.0f,0.0f);
		 
		
		mat->SetColor ("_TopColor",     TopColor    );
		mat->SetColor ("_HorizonColor", HorizonColor);
		mat->SetVector("_SunVector",    SunVector.normalized());
		mat->SetColor ("_SunDecay",     SunDecay    );

		mat->SetDepthFunction(Material_DepthFunction_LEQUAL);

		meshRenderer = new MeshRenderer(mesh, mat); // Ownership is with this class. MeshRenderer is Usually handeled by GameObject, not here. 
		// To Do: Think of a better architecture for this. 
	}
	ProceduralSkyBox::ProceduralSkyBox(Material * mat)
	{
		mesh = new Mesh();
		ResourceManager::Instance().RegisterMesh(mesh);

		PopulateVertexPosition();

		meshRenderer = new MeshRenderer(mesh, mat); // Ownership is with this class. MeshRenderer is Usually handeled by GameObject, not here. 
		// To Do: Think of a better architecture for this. 

	}

	ProceduralSkyBox::~ProceduralSkyBox()
	{
		delete meshRenderer;
	}

	void ProceduralSkyBox::Render(Renderer & renderer, const Matrix4x4 & viewProjection)
	{
		meshRenderer->Render(renderer, viewProjection);
	}
	void ProceduralSkyBox::PopulateVertexPosition()
	{
	      
			mesh->VertexPositions.push_back(Vector3(-1.0f,  1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f, -1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f, -1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f, -1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f,  1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f,  1.0f, -1.0f));
			
			mesh->VertexPositions.push_back(Vector3(-1.0f, -1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f, -1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f,  1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f,  1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f,  1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f, -1.0f,  1.0f));
			
			mesh->VertexPositions.push_back(Vector3( 1.0f, -1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f, -1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f,  1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f,  1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f,  1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f, -1.0f, -1.0f));
			
			mesh->VertexPositions.push_back(Vector3(-1.0f, -1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f,  1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f,  1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f,  1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f, -1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f, -1.0f,  1.0f));
			
			mesh->VertexPositions.push_back(Vector3(-1.0f,  1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f,  1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f,  1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f,  1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f,  1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f,  1.0f, -1.0f));
			
			mesh->VertexPositions.push_back(Vector3(-1.0f, -1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f, -1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f, -1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f, -1.0f, -1.0f));
			mesh->VertexPositions.push_back(Vector3(-1.0f, -1.0f,  1.0f));
			mesh->VertexPositions.push_back(Vector3( 1.0f, -1.0f,  1.0f));

		
			// populate indexbuffer. Above is a triangle stripes, so I can just do 0 to 40 in the index buffer.
			// TO DO: Optimize later and get rid of duplicated vertices.

			for (int i = 0; i < mesh->VertexPositions.size(); i++) {
				mesh->triangles.push_back(i);
			}
			mesh->VertexCount = mesh->VertexPositions.size();

	}
}


