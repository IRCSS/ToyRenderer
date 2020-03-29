#include "Time.h"
#include <ctime>

namespace ToyRenderer {

	float Time::lastFrameTime;
	float Time::deltaTime;

	float Time::GetTime()
	{
		return lastFrameTime;
	}
	float Time::GetDeltaTime()
	{
		return deltaTime;
	}
	Time::Time()
    {
		lastFrameTime = (float)clock();
		deltaTime = 0.0;
    }
	void Time::Update()
	{
		float currentTime = (float)clock();
		deltaTime = currentTime - lastFrameTime;
	}
}
