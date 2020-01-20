#pragma once

#include "Mesh.h"


namespace ToyRenderer {
	
	class MeshLoader {
		
	public:
		static Mesh LoadTinyObj(const std::string& filePath);


	};

}