#include "Vignetting.h"
#include "rendering/Shader.h"
#include "rendering/Material.h"
#include "rendering/Graphics.h"
#include "world/Time.h"
#include "log/Log.h"
namespace ToyRenderer {
	namespace PostProcessing {
        Vignetting::Vignetting()
        {
			vignettingShader   = new Shader("postProcess/vignetting");
			vignettingMaterial = new Material(vignettingShader);
			vignettingMaterial->SetDepthFunction(Material_DepthFunction_ALWAYS);
			vignettingMaterial->EnableZTest(false);
			vignettingMaterial->EnableZWrite(false);
			vignettingMaterial->SetFloat("_Time", Time::GetTime());
        }
		Vignetting::~Vignetting()
		{
			delete vignettingShader;
			delete vignettingMaterial;
		}
		void Vignetting::OnPostRender(Rendering::FrameBuffer & src, Rendering::FrameBuffer & dst, Renderer & renderer)
		{
			vignettingMaterial->SetFloat("_Time", Time::GetTime());

			Rendering::Graphic::Blit(src, dst, *vignettingMaterial, renderer);
		}
    }
}
