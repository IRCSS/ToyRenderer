#pragma once

#include "Core.h"
#include <vector>
#include "Components/Component.h"
#include "ProceduralSkyBox.h"




namespace ToyRenderer {
    class Matrix4x4;
	class Scene;
	class MeshRenderer;
	class Transform;
	class Color;

	namespace Rendering {
		class PostProcess;
		class FrameBuffer;
	}




	class TOYRENDERER_API Camera : public Component {
	
	// PUBLIC ======================================================================================

	public: 

		 Camera();
		 Camera(Scene* scene);
		 ~Camera();
		 void OnRender() override;
		 void UpdateRenderLists();

		 void AddPostProcessToStack( Rendering::PostProcess* toAdd);

		 Matrix4x4 ProjectionMatrix()        const;
		 Matrix4x4 VPMatrix()                const;
		 Matrix4x4 VP_NoTranslation_Matrix() const;
	public: 
		float fov, nearClip, farClip;

    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private:
		void InitiateFrontBuffers(const int width, const int Height);


    #pragma warning( disable : 4251)  
    // std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. Private stuff wont be inlined so I will disable them
	private:
		Scene*                               scene;
		std::vector<MeshRenderer*>           activeMeshRenderers;
		Transform*                           transform;
		ProceduralSkyBox*                    skybox;
		std::vector<Rendering::PostProcess*> postProcessStack;
		
		Rendering::FrameBuffer*              m_FrontBufferPing;
		Rendering::FrameBuffer*              m_FrontBufferPong;

    #pragma warning(default:4251) // Turning the 4251 back on
	};
}