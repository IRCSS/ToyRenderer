#include "MoveCamera.h"
#include "InputMaster.h"
#include "maths/Vector2.h"
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

		if (!ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::RightMouseButton)) {
			ToyRenderer::InputMaster::mouse.SetMouseVisible(true);
			return;
		}
		ToyRenderer::InputMaster::mouse.SetMouseVisible(false);
		float speedBoast = 1.0f;

		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::LeftShift)) speedBoast = speedMultiplyer;

		Vector3 p = m_cam->position;

		float x = 0.0f;

		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::D)) x-= movementSpeed;
		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::A)) x+= movementSpeed;

		float z = 0.0f;

		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::S)) z -= movementSpeed;
		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::W)) z += movementSpeed;

		float y = 0.0f;

		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::E)) y += movementSpeed;
		if (ToyRenderer::InputMaster::GetKey(ToyRenderer::KeyName::Q)) y -= movementSpeed;


		p += (-x * m_cam->Right() + y * m_cam->Up() + -z * m_cam->Foward())*speedBoast;

		m_cam->position = p;

		Vector2 mouseInput = ToyRenderer::InputMaster::mouse.GetMouseDelta();


		float rotationY = (-mouseInput.x)* rotationSpeed;
		float rotationX = (-mouseInput.y)* rotationSpeed;

		//std::cout << rotationX << " rotation x, " << rotationY <<" rotation y." << std::endl;

		   m_cam->RotateAroundOrigin(m_cam->Right(), rotationX);
		   m_cam->RotateAroundOrigin(vector3_up, rotationY);
	}
}


