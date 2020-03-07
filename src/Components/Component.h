#pragma once
namespace ToyRenderer {
	class Component {
	public:
	               Component();
	  virtual     ~Component();
	  virtual void OnUpdate(float deltaTime);
	  virtual void OnRender();
	  virtual void OnImGuiRender();
	};
}