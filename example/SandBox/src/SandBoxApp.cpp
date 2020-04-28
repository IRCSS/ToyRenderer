#include <ToyRenderer.h>
class Sandbox : public ToyRenderer::ToyRendererApp {

public: 
	Sandbox() {
	
	}
	~Sandbox() {

	}

};

ToyRenderer::ToyRendererApp* ToyRenderer::CreateApplication() 
{
	return new Sandbox();
}