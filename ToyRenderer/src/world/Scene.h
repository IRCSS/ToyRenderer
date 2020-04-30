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
    #pragma warning( disable : 4251)  
    // std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. Private stuff wont be inlined so I will disable them
		std::vector<GameObject*> sceneObjects;
    #pragma warning(default:4251) // Turning the 4251 back on
		Renderer* renderer;
	
	};
}