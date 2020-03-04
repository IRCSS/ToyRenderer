#pragma once
#include "Components/Scripts/Script.h"
#include "Components/Transform.h"
namespace Behaviours {

	class MoveCamera : Script {

	public: 
		ToyRenderer::Transform* m_cam;

	private:
		const float movementSpeed = 0.01f;
		const float rotationSpeed = 0.005f;

	public:
		MoveCamera();
		MoveCamera( ToyRenderer::Transform* cam);
		virtual ~MoveCamera();

		virtual void OnUpdate(float deltaTime);



	};

}