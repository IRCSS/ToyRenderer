#pragma once

#include "rendering/RawMesh.h"


namespace ToyRenderer {
	
	class MeshLoader {
		
	public:
		static RawMesh* LoadTinyObj(const char* filename, const char* basepath = NULL);


	};

}