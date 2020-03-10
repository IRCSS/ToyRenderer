#pragma once
#include <vector>
#include "Components/Component.h"

class Matrix4x4;

namespace ToyRenderer {
	class Scene;
	class MeshRenderer;
	class Transform;


	class Camera : public Component {
	
	public: 
		float fov, nearClip, farClip;

	private:
		Scene* scene;
		std::vector<MeshRenderer*> activeMeshRenderers;
		Transform* transform;
	
	public: 

		 Camera();
		 Camera(Scene* scene);
		 void OnRender() override;
		 void UpdateRenderLists();
		 Matrix4x4 ProjectionMatrix() const;
		 Matrix4x4 VPMatrix() const;
	};
}