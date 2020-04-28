#pragma once
#include "Core.h"
#include "rendering/Mesh/Mesh.h"
namespace ToyRenderer {

	static class TOYRENDERER_API PrimitivFactory {

	// PUBLIC ======================================================================================
	public: 
		static Mesh* CreatePlane();
		static Mesh* CreateFullScreenQuad();
	};

}