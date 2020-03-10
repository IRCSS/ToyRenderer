#include "Camera.h"
#include "world/Scene.h"
#include "rendering/MeshRenderer.h"
#include "maths/Matrix4x4.h"
#include "Components/Transform.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Settings.h"

namespace ToyRenderer {
	Camera::Camera()
	{
	}
	Camera::Camera(Scene * in_Scene) : scene(in_Scene)
	{
		if (!transform) transform = gameObject->GetComponent<Transform>();
		UpdateRenderLists();
		fov      = 60.0f;
		nearClip = 0.01f;
		farClip  = 100.0f;

	}
	void Camera::OnRender()
	{
		if (!transform) transform = gameObject->GetComponent<Transform>();

		Matrix4x4 vp = VPMatrix();

		for (std::vector<MeshRenderer*>::size_type i = 0; i != activeMeshRenderers.size(); i++) {
			
			activeMeshRenderers[i]->Render(*scene->renderer,vp);
		}

	}
	void Camera::UpdateRenderLists()
	{
		activeMeshRenderers = scene->GetAllGameObjectsWithComponent<MeshRenderer>();
	}
	Matrix4x4 Camera::ProjectionMatrix() const
	{
		Matrix4x4 projection = Matrix4x4(glm::perspective(glm::radians(fov), (float)Settings::WindowWidth / (float)Settings::WindowHeigth, nearClip, farClip));
		return projection;
	}
	Matrix4x4 Camera::VPMatrix() const
	{

		Matrix4x4 projection = ProjectionMatrix();
		Matrix4x4 vp = projection * transform->worldToLocal();

		return vp;
	}
}

