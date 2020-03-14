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
		
		UpdateRenderLists();
		fov      = 60.0f;
		nearClip = 0.01f;
		farClip  = 100.0f;

		skybox = new ProceduralSkyBox();
	}
	Camera::~Camera()
	{
		delete skybox;
	}
	void Camera::OnRender()
	{

		if (!transform && gameObject) transform = gameObject->GetComponent<Transform>();

		Matrix4x4 vp = VP_NoTranslation_Matrix();
		skybox->Render(*scene->renderer, vp);

		  vp = VPMatrix();

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

	Matrix4x4 Camera::VP_NoTranslation_Matrix() const
	{
		Matrix4x4 viewNoTranslation = transform->worldToLocal();
		viewNoTranslation.SetColumn(3, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		return  ProjectionMatrix() * viewNoTranslation;
	}


}

