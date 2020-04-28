#pragma once
#include "Core.h"
#include "rendering/RawMesh.h"


namespace ToyRenderer {
	
	class TOYRENDERER_API MeshLoader {
	
	// PUBLIC ======================================================================================		
	
	public:
		static RawMesh* LoadTinyObj(const char* filename, const char* basepath = NULL);


	};

}