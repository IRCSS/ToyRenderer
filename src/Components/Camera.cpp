#include "Camera.h"
#include "world/Scene.h"
#include "rendering/MeshRenderer.h"
namespace ToyRenderer {
	Camera::Camera()
	{
	}
	Camera::Camera(Scene * in_Scene) : scene(in_Scene)
	{
		UpdateRenderLists();
	}
	void Camera::OnRender()
	{


	}
	void Camera::UpdateRenderLists()
	{
		activeMeshRenderers = scene->GetAllGameObjectsWithComponent<MeshRenderer>();
	}
}

