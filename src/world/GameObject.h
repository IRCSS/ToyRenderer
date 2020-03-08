#pragma once


#include <vector>
#include "Components/Component.h"
namespace ToyRenderer {

	class GameObject {
		
	public:

		std::string name;

	private:
		std::vector<Component*> components;

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
		

	};
};