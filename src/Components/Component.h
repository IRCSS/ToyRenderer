#pragma once
#include "world/GameObject.h"
namespace ToyRenderer {
	class Component {

	public:
		GameObject* gameObject;

	public:
	               Component();
	  virtual     ~Component();
	  virtual void OnUpdate(float deltaTime);
	  virtual void OnRender();
	  virtual void OnImGuiRender();
	};
}