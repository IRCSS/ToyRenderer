#pragma once

class Shader;

namespace ToyRenderer {
	class MeshRenderer;
	class Material;
	class Mesh;

	namespace Rendering {
		class FrameBuffer;
		class Graphic {

			// The mesh, shader and the material need to be delete by this class. The texture is managed by framebuffers
		private: 
			static MeshRenderer* m_fullScreenQuadRenderer;
			static Material*     m_defaultMaterial;
			static Mesh*         m_fullScreenQuadMesh;
			static Shader*       m_defaultPassThroughShader;


		public:

			// Not a smart design. I have to rethink this later
			 Graphic();
			~Graphic();

			// Graphics
			static void Blit(const FrameBuffer& src, const FrameBuffer& dst);
			static void Blit(const FrameBuffer& src, const FrameBuffer& dst, Material& mat);
		};
	}
}