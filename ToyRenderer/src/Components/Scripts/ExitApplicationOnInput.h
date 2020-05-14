#pragma once
#include "Core.h"
#include "Components/Scripts/Script.h"
namespace ToyRenderer {

	class InputMaster;
	enum  KeyName;
	namespace Behaviours {


		class TOYRENDERER_API ExitApplicationOnInput : public Script {

		// PUBLIC ======================================================================================
		public:
			 ExitApplicationOnInput();
			~ExitApplicationOnInput();

			void OnUpdate(float deltaTime) override;

		public: 
			KeyName exitKey;
		};
	}
}