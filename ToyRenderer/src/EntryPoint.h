#pragma once
#ifdef TOYRENDERER_PLATFORM_WINDOWS

extern ToyRenderer::ToyRendererApp* ToyRenderer::CreateApplication();

void main(int argc, char** argv) {
	auto app = ToyRenderer::CreateApplication();
	app->Run();
	delete app;
}

#endif // TOYRENDERER_PLATFORM_WINDOWS
