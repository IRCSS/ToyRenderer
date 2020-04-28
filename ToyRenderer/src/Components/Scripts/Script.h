#pragma once
#include "Core.h"
#include "Components/Component.h"
namespace ToyRenderer {
	namespace Behaviours {

		class TOYRENDERER_API Script : public ToyRenderer::Component {

	// PUBLIC ======================================================================================
		public:
			Script() {};
			virtual ~Script() {}

			virtual void OnUpdate(float deltaTime) {}
			virtual void OnRender() {}
			virtual void OnImGuiRender() {}
		};

	}
}