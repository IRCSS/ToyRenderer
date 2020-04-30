#pragma once

#include "Core.h"
#include <vector>
#include "Components/Component.h"



namespace ToyRenderer {

	class TOYRENDERER_API GameObject {

	// PUBLIC ======================================================================================		
	public: 
		GameObject();
		void OnUpdate(float deltaTime);
		void OnRender();
		void OnGUI();

		// Replace this later with a unordered map iwth typid as string key and vector of components pointer as value.
		// it will reduce the access time for GetComponent.

		template<typename T>
		T* GetComponent() const {
			
			for (std::vector<Component*>::size_type i = 0; i != components.size(); i++) {
				T* isT = dynamic_cast<T*> (components[i]);
				if (!isT) continue;
				return isT;
			}
			return NULL;
		}

		template<typename T>
		void AddComponent(T* toAdd) {
			Component* cp = (Component*)toAdd;
			cp->gameObject = this;
			components.push_back(cp);

		}
    #pragma warning( disable : 4251)  
	// std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. 
	public:

		std::string name;
    #pragma warning(default:4251) // Turning the 4251 back on

    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
    #pragma warning( disable : 4251)  
    // std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. Private stuff wont be inlined so I will disable them
	private:
		std::vector<Component*> components;

    #pragma warning(default:4251) // Turning the 4251 back on
	};
};