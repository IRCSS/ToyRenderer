#pragma once
#include "Core.h"
#include "rendering/PostProcess.h"
namespace ToyRenderer {
    class Renderer;
    class Shader;
	class Material;

	namespace Rendering {
		class FrameBuffer;
	}

	namespace PostProcessing{

		class TOYRENDERER_API Vignetting : public ToyRenderer::Rendering::PostProcess {
		// PUBLIC ======================================================================================
		public:
			 Vignetting();
			~Vignetting() override;

			void OnPostRender(Rendering::FrameBuffer& src, Rendering::FrameBuffer& dst, Renderer& renderer) override;

        // ______________________________________________________________________________________________
	    // PRIVATE ======================================================================================

		private:
			Shader*   vignettingShader;
 			Material* vignettingMaterial;


		};

	}
}
