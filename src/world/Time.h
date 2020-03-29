#pragma once
namespace ToyRenderer {
	
	
	class Time {
	public: 
		static float GetTime();
		static float GetDeltaTime();
	
		Time();
		void Update();

	private:
		static float lastFrameTime;
		static float deltaTime;
	};
}