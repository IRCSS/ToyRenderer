#include "AudioPlayer.h"
#include "Audio/AudioEngine.h"
#include "managers/AudioAssembly.h"
#include "managers/ResourceManager.h"
#include "log/Log.h"

namespace ToyRenderer {
	AudioPlayer::AudioPlayer() : m_AudioClip(nullptr), m_looped(false), m_autoPlayer(false)
	{
	}

	AudioPlayer::AudioPlayer(const char * AudioSourceTagName) : m_AudioClip(nullptr), m_looped(false), m_autoPlayer(false)
	{
		m_AudioClip = ResourceManager::Instance().audioAssembly->GetAudioClipWitname(AudioSourceTagName);
		ENGINE_LOG_WARN("attempted to load an AudioSource with name: {}, however the Audio Assembly holds no such audiosource", AudioSourceTagName);
	}

	AudioPlayer::AudioPlayer(const char * AudioSourceTagName, bool looped, bool autoPlay) : m_AudioClip(nullptr), m_looped(looped), m_autoPlayer(autoPlay)
	{
		m_AudioClip = ResourceManager::Instance().audioAssembly->GetAudioClipWitname(AudioSourceTagName);
		ENGINE_LOG_WARN("attempted to load an AudioSource with name: {}, however the Audio Assembly holds no such audiosource", AudioSourceTagName);
	}

	AudioPlayer::~AudioPlayer()
	{
	}

	void AudioPlayer::OnUpdate(float deltaTime)
	{
	}

	void AudioPlayer::Play()
	{
		AudioEngine::Instance().Play(m_AudioClip);
	}



}
