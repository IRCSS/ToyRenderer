#pragma once
#include <vector>
#include "Components/Component.h"
#include "ProceduralSkyBox.h"
class Matrix4x4;

namespace ToyRenderer {
	class Scene;
	class MeshRenderer;
	class Transform;
	class Color;

	namespace Rendering {
		class PostProcess;
		class FrameBuffer;
	}
	class Camera : public Component {
	
	public: 
		float fov, nearClip, farClip;

	private:
		Scene* scene;
		std::vector<MeshRenderer*> activeMeshRenderers;
		Transform* transform;
		ProceduralSkyBox* skybox;
		std::vector<Rendering::PostProcess*> postProcessStack;
		
		Rendering::FrameBuffer* m_FrontBufferPing;
		Rendering::FrameBuffer* m_FrontBufferPong;

		
	
	public: 

		 Camera();
		 Camera(Scene* scene);
		 ~Camera();
		 void OnRender() override;
		 void UpdateRenderLists();

		 void AddPostProcessToStack( Rendering::PostProcess* toAdd);

		 Matrix4x4 ProjectionMatrix() const;
		 Matrix4x4 VPMatrix()         const;
		 Matrix4x4 VP_NoTranslation_Matrix() const;

	private:
		void InitateFrontBuffers(const int width, const int Height);
	};
}