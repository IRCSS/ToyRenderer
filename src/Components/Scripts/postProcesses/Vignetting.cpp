#include "Vignetting.h"
#include "rendering/Shader.h"
#include "rendering/Material.h"
#include "rendering/Graphics.h"
namespace ToyRenderer {
	namespace PostProcessing {
        Vignetting::Vignetting()
        {
			vignettingShader   = new Shader("res/shaders/postProcess_Vignetting.shader");
			vignettingMaterial = new Material(vignettingShader);
			vignettingMaterial->SetDepthFunction(Material_DepthFunction_ALWAYS);
			vignettingMaterial->EnableZTest(false);
			vignettingMaterial->EnableZWrite(false);
        }
		Vignetting::~Vignetting()
		{
			delete vignettingShader;
			delete vignettingMaterial;
		}
		void Vignetting::OnPostRender(Rendering::FrameBuffer & src, Rendering::FrameBuffer & dst, Renderer & renderer)
		{
			Rendering::Graphic::Blit(src, dst, *vignettingMaterial, renderer);
		}
    }
}
