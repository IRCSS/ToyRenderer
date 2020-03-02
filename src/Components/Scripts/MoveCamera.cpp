#include "MoveCamera.h"
#include "InputMaster.h"

namespace Behaviours {
	MoveCamera::MoveCamera()
	{
	}

	MoveCamera::MoveCamera(ToyRenderer::Transform* cam) : m_cam(cam)
	{
	}

    MoveCamera::~MoveCamera()
	{
	}

	void MoveCamera::OnUpdate(float deltaTime)
	{
		Vector3 p = m_cam->position;

		float x = 0.0f;

		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::D)) x-= movementSpeed;
		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::A)) x+= movementSpeed;

		float z = 0.0f;

		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::S)) z -= movementSpeed;
		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::W)) z += movementSpeed;

		float y = 0.0f;

		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::E)) y -= movementSpeed;
		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::Q)) y += movementSpeed;

		p += x * m_cam->Right() + y * m_cam->Up() + z * m_cam->Foward();

		m_cam->position = p;

	}
}


