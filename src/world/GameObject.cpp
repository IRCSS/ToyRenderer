#include "GameObject.h"

namespace ToyRenderer {
    GameObject::GameObject()
	{
	}
	void GameObject::OnUpdate(float deltaTime)
	{
		for (std::vector<Component*>::size_type i = 0; i != components.size(); i++) {

			components[i]->OnUpdate(deltaTime);
		}
	}
	void GameObject::OnRender()
	{

		for (std::vector<Component*>::size_type i = 0; i != components.size(); i++) {

			components[i]->OnRender();
		}
	}
	void GameObject::OnGUI()
	{
		for (std::vector<Component*>::size_type i = 0; i != components.size(); i++) {

			components[i]->OnImGuiRender();
		}
	}
}
