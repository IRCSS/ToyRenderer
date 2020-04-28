#include <ToyRenderer.h>
class Sandbox : public ToyRenderer::ToyRendererApp {

public: 
	Sandbox() {
	
		CLIENT_LOG_INFO("sand box has been initialized");
	}
	~Sandbox() {

	}

};

ToyRenderer::ToyRendererApp* ToyRenderer::CreateApplication() 
{
	return new Sandbox();
}