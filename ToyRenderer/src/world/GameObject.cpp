#include "GameObject.h"
#include "log/Log.h"
namespace ToyRenderer {
    GameObject::GameObject() : m_transfrom(nullptr)
	{
	};
	GameObject::~GameObject()
	{
		for (std::vector<Component*>::iterator i = components.begin(); i != components.end(); ++i)
			delete *i;
		components.clear();
	}
	void GameObject::OnStart()
	{
		for (std::vector<Component*>::size_type i = 0; i != components.size(); i++) {

			components[i]->OnStart();
		}
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
	Transform* GameObject::GetTransfrom()
	{
		if (m_transfrom != nullptr) return m_transfrom;

		m_transfrom = this->GetComponent<Transform>();

		if (m_transfrom == nullptr) ENGINE_LOG_ERROR("Attempted to access the Transfrom component of the Gameobject {}, however Gameobject {} has no such component",name,name);
		return m_transfrom;

	}
}
