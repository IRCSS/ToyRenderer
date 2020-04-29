#pragma once
#include "Core.h"
namespace ToyRenderer {
	

	class TOYRENDERER_API Time {

	// PUBLIC ======================================================================================	
	
	public: 
		static float GetTime();
		static float GetDeltaTime();
	
		Time();
		void Update();

    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private:
		static float lastFrameTime;
		static float deltaTime;
	};
}