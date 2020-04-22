#pragma once
#include "rendering/PostProcess.h"
class Renderer;
class Shader;
namespace ToyRenderer {
	class Material;
	namespace Rendering {
		class FrameBuffer;
	}

	namespace PostProcessing{

		class Vignetting : public ToyRenderer::Rendering::PostProcess {
		private:
			Shader*   vignettingShader;
 			Material* vignettingMaterial;

		public:
			 Vignetting();
			~Vignetting() override;

			void OnPostRender(Rendering::FrameBuffer& src, Rendering::FrameBuffer& dst, Renderer& renderer) override;

		};

	}
}
