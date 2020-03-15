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

		// Sort out passed
		std::vector<MeshRenderer*> opaquePassRenderes      = std::vector<MeshRenderer*>();
		std::vector<MeshRenderer*> transparentPassRenderers = std::vector<MeshRenderer*>();
		
		for (std::vector<MeshRenderer*>::size_type i = 0; i != activeMeshRenderers.size(); i++) {

			int passID= activeMeshRenderers[i]->material->GetPass();
			switch (passID)
			{
			case Material_PASS_OPAQUE:      opaquePassRenderes.push_back(activeMeshRenderers[i]);      break;
			case Material_PASS_TRANSPARENT: transparentPassRenderers.push_back(activeMeshRenderers[i]); break;
			}
		}

		// RENDER ORDER:
		// OPAQUE
		// SKYBOX
		// TRANSPARENT

		Matrix4x4 vp = VPMatrix();
		Matrix4x4 vp_noTranslation = VP_NoTranslation_Matrix();
		
		for (std::vector<MeshRenderer*>::size_type i = 0; i != opaquePassRenderes.size(); i++) {

			opaquePassRenderes[i]->Render(*scene->renderer, vp);
		}

		skybox->Render(*scene->renderer, vp_noTranslation);

		for (std::vector<MeshRenderer*>::size_type i = 0; i != transparentPassRenderers.size(); i++) {
			
			transparentPassRenderers[i]->Render(*scene->renderer,vp);
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

