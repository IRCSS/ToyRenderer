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
			
			for (std::vector<int>::size_type i = 0; i != components.size(); i++) {
				T* isT = dynamic_cast<T*> (components[i]);
				if (!isT) continue;
				return isT;
			}
			return NULL;
		}

		template<typename T>
		void AddComponent(T* toAdd) {
			components.push_back((Component*) toAdd);
			std::cout << components.size() << std::endl;
		}
		

	};
};