#pragma once

#include "Mesh.h"


namespace ToyRenderer {
	
	class MeshLoader {
		
	public:
		static Mesh* LoadTinyObj(const char* filename, const char* basepath = NULL, bool triangulate = true);


	};

}