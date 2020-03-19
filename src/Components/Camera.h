#pragma once
#include <vector>
#include "Components/Component.h"
#include "ProceduralSkyBox.h"
class Matrix4x4;

namespace ToyRenderer {
	class Scene;
	class MeshRenderer;
	class Transform;
	class Color;

	class Camera : public Component {
	
	public: 
		float fov, nearClip, farClip;

	private:
		Scene* scene;
		std::vector<MeshRenderer*> activeMeshRenderers;
		Transform* transform;
		ProceduralSkyBox* skybox;

		
	
	public: 

		 Camera();
		 Camera(Scene* scene);
		 ~Camera();
		 void OnRender() override;
		 void UpdateRenderLists();
		 Matrix4x4 ProjectionMatrix() const;
		 Matrix4x4 VPMatrix()         const;
		 Matrix4x4 VP_NoTranslation_Matrix() const;
	};
}