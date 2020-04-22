#pragma once
#include "rendering/Mesh/Mesh.h"
namespace ToyRenderer {

	static class PrimitivFactory {

	public: 
		static Mesh* CreatePlane();
		static Mesh* CreateFullScreenQuad();
	};

}