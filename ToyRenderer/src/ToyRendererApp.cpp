#include "ToyRendererApp.h"
#include "log/Log.h"
#include <iostream>
namespace ToyRenderer {

	

	ToyRendererApp::ToyRendererApp()
	{
		ToyRenderer::Log::Initialize();

	}

	ToyRendererApp::~ToyRendererApp()
	{
	}

	void ToyRendererApp::Run()
	{
		while (true) {  };
	}

}