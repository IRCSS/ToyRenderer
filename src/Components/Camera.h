#pragma once
#include <vector>
#include "Components/Component.h"

namespace ToyRenderer {
	class Scene;
	class MeshRenderer;
	class Camera : public Component {
	private:
		Scene* scene;
		std::vector<MeshRenderer*> activeMeshRenderers;
	
	public: 

		 Camera();
		 Camera(Scene* scene);
		 void OnRender() override;
		 void UpdateRenderLists();
	};
}