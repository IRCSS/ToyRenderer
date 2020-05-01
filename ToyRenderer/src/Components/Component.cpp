#include "Component.h"
namespace ToyRenderer {
	Component::Component() : gameObject(nullptr)
	{
	}
	Component::~Component()
	{
	}
	void Component::OnUpdate(float deltaTime)
	{
	}
	void Component::OnRender()
	{
	}
	void Component::OnImGuiRender()
	{
	}
}