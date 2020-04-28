#pragma once
#include "Core.h"

namespace ToyRenderer {

    class Shader;
    class Renderer;
	class MeshRenderer;
	class Material;
	class Mesh;


	namespace Rendering {
		class FrameBuffer;

		class TOYRENDERER_API Graphic {

	    // PUBLIC ======================================================================================
		public:

			// Not a smart design. I have to rethink this later
			 Graphic();
			~Graphic();

			//Delete the copy constructor/assignment 
			Graphic(const Graphic &)            = delete;

			// Graphics
			static void Blit(const FrameBuffer& src, const FrameBuffer& dst, Renderer& renderer);
			static void Blit(const FrameBuffer& src, const FrameBuffer& dst, Material& mat, Renderer& renderer);
			static void BlitToBackBuffer(const FrameBuffer& src,  Renderer& );

			// The mesh, shader and the material need to be delete by this class. The texture is managed by framebuffers
		// ______________________________________________________________________________________________
	    // PRIVATE ======================================================================================

		private: 
			static MeshRenderer* m_fullScreenQuadRenderer;
			static Material*     m_defaultMaterial;
			static Mesh*         m_fullScreenQuadMesh;
			static Shader*       m_defaultPassThroughShader;

		};
	}
}