#include "PrimitiveFactory.h"
#include "ResourceManager.h"
#include "maths/Vector3.h"
#include "maths/Vector2.h"
namespace ToyRenderer {
	Mesh* PrimitivFactory::CreatePlane()
	{
		Mesh* toReturn = new Mesh();
		ResourceManager::Instance().RegisterMesh(toReturn);

	 

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

		toReturn->VertexCount = 4;
		return toReturn;
	}
}

