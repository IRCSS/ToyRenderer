#pragma once
#include "Components/Component.h"
namespace Behaviours {

	class Script : ToyRenderer::Component {
		
	public:
		Script() {};
		virtual ~Script() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

}