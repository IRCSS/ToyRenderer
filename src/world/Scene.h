#pragma once
#include "world/GameObject.h" 
namespace ToyRenderer {
	class Scene {
	
	public:
		std::vector<GameObject> GameObject;
		
	
	public:
		Scene();

		void OnUpdate(float deltaTime) const;
		void OnRender() const;
		void OnGUI()    const;


	};
}