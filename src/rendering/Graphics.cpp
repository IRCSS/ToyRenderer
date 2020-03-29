#include "Graphics.h"
#include "rendering/MeshRenderer.h"
#include "rendering/Material.h"
#include "rendering/Mesh/Mesh.h"
#include "rendering/Mesh/PrimitiveFactory.h"
#include "rendering/Shader.h"
#include "rendering/FrameBuffer.h"
#include "rendering/RHI/RHI.h"
namespace ToyRenderer {
	namespace Rendering {

		MeshRenderer* Graphic::m_fullScreenQuadRenderer;
		Material*     Graphic::m_defaultMaterial;
		Mesh*         Graphic::m_fullScreenQuadMesh;
		Shader*       Graphic::m_defaultPassThroughShader;

		Graphic::Graphic( ) 
		{
			m_fullScreenQuadMesh       = PrimitivFactory::CreateFullScreenQuad();
			m_defaultPassThroughShader = new Shader("res/shaders/postProcess_PassThrough.shader");
			m_defaultMaterial          = new Material(m_defaultPassThroughShader);
			m_defaultMaterial->SetDepthFunction(Material_DepthFunction_ALWAYS);
			m_defaultMaterial->EnableZTest(false);
			m_defaultMaterial->EnableZWrite(false);
			m_fullScreenQuadRenderer   = new MeshRenderer(m_fullScreenQuadMesh, m_defaultMaterial);

		}
		Graphic::~Graphic()
		{
			delete m_defaultMaterial;
			delete m_fullScreenQuadRenderer;
			delete m_fullScreenQuadMesh;
			delete m_defaultPassThroughShader;
		}
		void Graphic::Blit(const FrameBuffer & src, const FrameBuffer & dst, Renderer& renderer)
		{
			dst.Bind();
			m_fullScreenQuadRenderer->material = m_defaultMaterial;
			m_defaultMaterial->SetTexture("fbo_texture", src.GetTexturePointer());
			m_fullScreenQuadRenderer->Render(renderer);
			dst.UnBind();
		}
		void Graphic::Blit(const FrameBuffer & src, const FrameBuffer & dst, Material & mat, Renderer& renderer) // The material is handeled outside of this class. 
		{
			dst.Bind();
			m_fullScreenQuadRenderer->material = &mat;
			m_fullScreenQuadRenderer->material->SetTexture("fbo_texture", src.GetTexturePointer());
			m_fullScreenQuadRenderer->Render(renderer);
			dst.UnBind();
		}
		void Graphic::BlitToBackBuffer(const FrameBuffer & src,  Renderer& renderer)
		{
			RHI::BindBackBuffer();
			m_fullScreenQuadRenderer->material = m_defaultMaterial;
			m_defaultMaterial->SetTexture("fbo_texture", src.GetTexturePointer());
			m_fullScreenQuadRenderer->Render(renderer);
	

		}
	}
}



