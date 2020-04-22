#pragma once
#include "Components/Scripts/Script.h"
#include "Components/Transform.h"
namespace Behaviours {

	class MoveCamera :public Script {

	public: 
		ToyRenderer::Transform* m_cam;

	private:
		const float movementSpeed   = 0.01f;
		const float rotationSpeed   = 0.005f;
		const float speedMultiplyer = 3.0f;

	public:
		MoveCamera();
		MoveCamera( ToyRenderer::Transform* cam);
		virtual ~MoveCamera();

		virtual void OnUpdate(float deltaTime);



	};

}