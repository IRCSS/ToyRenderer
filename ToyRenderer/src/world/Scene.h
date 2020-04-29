#pragma once
#include "Core.h"
#include "world/GameObject.h"
#include "rendering/Renderer.h"

namespace ToyRenderer {
	class TOYRENDERER_API Scene {
	// PUBLIC ======================================================================================	
	public:
		Scene();

		void OnUpdate(float deltaTime) const;
		void OnRender() const;
		void OnGUI()    const;

		template<typename T>
		std::vector<T*> GetAllGameObjectsWithComponent() {
			std::vector<T*> toReturn;

			for (std::vector<GameObject*>::size_type i = 0; i != sceneObjects.size(); i++) {
				T* object = sceneObjects[i]->GetComponent<T>();
				if (!object) continue;
				toReturn.push_back(object);
			}
			return toReturn;
		}

	public:
		std::vector<GameObject*> sceneObjects;
		Renderer* renderer;
	
	};
}