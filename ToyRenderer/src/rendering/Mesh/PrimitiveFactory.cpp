#include "PrimitiveFactory.h"
#include "managers/ResourceManager.h"
#include "maths/Vector3.h"
#include "maths/Vector2.h"
namespace ToyRenderer {
	Mesh* PrimitivFactory::CreatePlane()
	{
		Mesh* toReturn = new Mesh();
	

	 

		toReturn->VertexPositions = std::vector<Vector3>{Vector3(-1.0f,  0.0f,  1.0f),  
		                                                 Vector3( 1.0f,  0.0f,  1.0f),
				                                         Vector3( 1.0f,  0.0f, -1.0f),
														 Vector3(-1.0f,  0.0f, -1.0f)};

		toReturn->uv = std::vector<Vector2>{ Vector2(0.0f, 0.0f),
											 Vector2(1.0f, 0.0f),
											 Vector2(1.0f, 1.0f),
											 Vector2(0.0f, 1.0f) };

		toReturn->triangles = std::vector<unsigned int>{
			0, 1 ,2, // first Triagnle 
			2, 3, 0, // second Triangle
		};

		return toReturn;
	}
	Mesh * PrimitivFactory::CreateFullScreenQuad()
	{
		Mesh* toReturn = new Mesh();

		toReturn->VertexPositions = std::vector<Vector3>{ Vector3(-1.0f, -1.0f,  0.0f),
														  Vector3( 1.0f, -1.0f,  0.0f),
														  Vector3(-1.0f,  1.0f,  0.0f),
														  Vector3( 1.0f,  1.0f,  0.0f) };
		toReturn->triangles = std::vector<unsigned int>{
			0, 1 ,2, // first Triagnle 
			2, 1, 3, // second Triangle
		};

		return toReturn;
	}
}

