#pragma once
#include <vector>
#include "Components/Component.h"

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
	};
}