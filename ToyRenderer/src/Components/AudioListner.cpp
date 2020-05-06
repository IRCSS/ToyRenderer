#include "AudioListner.h"
#include "Components/ComponentsUtility.h"
#include "Transform.h"
#include "Audio/AudioEngine.h"
#include "Audio/AudioEngine.h"
namespace ToyRenderer {

	AudioListner::AudioListner()
	{
		

	}
	AudioListner::~AudioListner()
	{
	}
	void AudioListner::OnStart()
	{
		
		REQUIRE_COMPONENT(Transform, "Transform", "AudioListner");
		m_transform = this->gameObject->GetComponent<Transform>();

	}
	void AudioListner::OnUpdate(float deltaTime)
	{
		AudioEngine::Instance().SetAudioListner(m_transform);
	}
}
