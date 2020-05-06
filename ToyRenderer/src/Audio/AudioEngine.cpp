#include "AudioEngine.h"
#include "vendor/soloud/soloud.h"
#include "Audio/AudioClip.h"
#include "vendor/soloud/soloud_wav.h"
#include "Components/Transform.h"
namespace ToyRenderer {

	AudioEngine* AudioEngine::m_pSingelton = nullptr;

   	AudioEngine::AudioEngine() : m_soLoudBackend(nullptr)
   	{
		m_soLoudBackend = new SoLoud::Soloud; // object created
		m_soLoudBackend->init();              // back-end initialization
   	}

	AudioEngine::~AudioEngine()
	{
		m_soLoudBackend->deinit(); // Clean up!
		delete m_soLoudBackend;
	}

	void AudioEngine::OnUpdate(float deltaTime)
	{
		m_soLoudBackend->update3dAudio();
	}

	void AudioEngine::Play(AudioClip* toPlay)
	{
		m_soLoudBackend->play(toPlay->GetBackEndAudioSourceHandel());
	}

	void AudioEngine::Play(AudioClip * toPlay, const Transform * transform)
	{
		m_soLoudBackend->play3d(toPlay->GetBackEndAudioSourceHandel(), transform->position.x, transform->position.y, transform->position.z);
	}

	AudioEngine & AudioEngine::Instance()
	{
		if (!m_pSingelton) m_pSingelton = new AudioEngine();

		return *m_pSingelton;
	}

	void AudioEngine::Clear()
	{
		delete m_pSingelton;
		m_pSingelton = nullptr;
	}

}
