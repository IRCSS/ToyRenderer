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

		template<typename T>
		T* GetComponent() const {
			for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it) {
				T* isT = dynamic_cast<T*> (*it);
				if (!isT) continue;
				return isT;
			}
			return NULL;
		}

		template<typename T>
		void AddComponent(T* toAdd) {
			components.push_back((Component*) toAdd);
		}
		

	};
};