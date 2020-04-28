#pragma once
#include "Core.h"

namespace ToyRenderer {
	class GameObject;
	class TOYRENDERER_API Component {
	// PUBLIC ======================================================================================
	public:
	               Component();
	  virtual     ~Component();
	  virtual void OnUpdate(float deltaTime);
	  virtual void OnRender();
	  virtual void OnImGuiRender();

	public:
		GameObject* gameObject;


	};
}