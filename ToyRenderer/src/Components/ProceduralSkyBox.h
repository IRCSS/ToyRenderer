#pragma once
#include "Core.h"
#include "rendering/Renderer.h"
#include "rendering/Mesh/Mesh.h"
#include "rendering/MeshRenderer.h"
#include "rendering/Material.h"
#include "maths/Color.h"

namespace ToyRenderer {

    class Matrix4x4;

	class TOYRENDERER_API ProceduralSkyBox {
	
	// PUBLIC ======================================================================================
	public:
		ProceduralSkyBox();
		ProceduralSkyBox(Material* material);
		~ProceduralSkyBox();
		void Render(Renderer& renderer, const Matrix4x4& viewProjection);
	public:
		Color   TopColor;
		Color   HorizonColor;
		Vector4 SunVector;
		Color   SunDecay;
    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================

	private: 
		void PopulateVertexPosition();
	private:
		Mesh*         mesh;
		MeshRenderer* meshRenderer;

	};
}