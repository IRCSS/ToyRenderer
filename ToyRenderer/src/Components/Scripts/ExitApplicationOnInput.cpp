#include "ExitApplicationOnInput.h"
#include "ToyRendererApp.h"
#include "managers/input/InputMaster.h"

namespace ToyRenderer {
	namespace Behaviours {
		ExitApplicationOnInput::ExitApplicationOnInput() : exitKey(KeyName::Escape)
		{

		}

		ExitApplicationOnInput::~ExitApplicationOnInput()
		{
		}

		void ExitApplicationOnInput::OnUpdate(float deltaTime)
		{
			if (InputMaster::GetKeyDown(exitKey)) ToyRendererApp::Exit();
		}

	}
}
