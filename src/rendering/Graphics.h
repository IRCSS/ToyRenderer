#pragma once
namespace ToyRenderer {
	class MeshRenderer;
	class Material;
	namespace Rendering {
		class FrameBuffer;
		class Graphic {

		private: 
			static MeshRenderer* m_fullScreenQuad;
			static Material*     m_defaultMaterial;
			
			


		public:

			// Not a smart design. I have to rethink this later
			 Graphic();
			~Graphic();

			// Graphics
			static void Blit(const FrameBuffer& src, const FrameBuffer& dst);
		};
	}
}