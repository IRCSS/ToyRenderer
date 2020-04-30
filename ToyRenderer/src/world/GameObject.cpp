#include "GameObject.h"

namespace ToyRenderer {
    GameObject::GameObject()
	{
	}
	GameObject::~GameObject()
	{
		for (std::vector<Component*>::iterator i = components.begin(); i != components.end(); ++i)
			delete *i;
		components.clear();
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
