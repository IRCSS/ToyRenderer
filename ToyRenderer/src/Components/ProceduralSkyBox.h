#pragma once

#include "rendering/Renderer.h"
#include "rendering/Mesh/Mesh.h"
#include "rendering/MeshRenderer.h"
#include "rendering/Material.h"
#include "maths/Color.h"

class Matrix4x4;
namespace ToyRenderer {

	class ProceduralSkyBox {
	public:
		Color   TopColor;
		Color   HorizonColor;
		Vector4 SunVector;
		Color   SunDecay;

	private:
		Mesh*         mesh;
		MeshRenderer* meshRenderer;
	public:
		ProceduralSkyBox();
		ProceduralSkyBox(Material* material);
		~ProceduralSkyBox();
		void Render(Renderer& renderer, const Matrix4x4& viewProjection);

	private: 
		void PopulateVertexPosition();
	};
}