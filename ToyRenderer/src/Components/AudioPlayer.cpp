#include "AudioPlayer.h"
#include "Audio/AudioEngine.h"
#include "managers/AudioAssembly.h"
#include "managers/ResourceManager.h"
#include "log/Log.h"
#include "world/GameObject.h"
namespace ToyRenderer {
	AudioPlayer::AudioPlayer() : m_AudioClip(nullptr), m_looped(false), m_autoPlayer(false), m_3dSound(false), m_Handle(-1)
	{
	}


	AudioPlayer::AudioPlayer(const char * AudioSourceTagName, bool looped, bool autoPlay) : m_AudioClip(nullptr), m_looped(looped), m_autoPlayer(autoPlay), m_3dSound(false)
	{
		m_AudioClip = ResourceManager::Instance().audioAssembly->GetAudioClipWitname(AudioSourceTagName);
		if (m_AudioClip == nullptr) return;

		Settings_SetLooping();
		
	}

	AudioPlayer::~AudioPlayer()
	{
	}

	void AudioPlayer::OnStart()
	{
		if (m_autoPlayer) Play();
	}

	void AudioPlayer::OnUpdate(float deltaTime)
	{
	}

	void AudioPlayer::Play()
	{
		Settings_UpdateAll();
	
		if (!m_3dSound) {
			m_Handle = AudioEngine::Instance().Play(m_AudioClip);
			return;
		}

		if (gameObject == nullptr) {
			ENGINE_LOG_INFO("Audio Player attempted to play the audio {} as 3d audio, however the component is not attach to a gameobject.", m_AudioClip->GetName());
			m_Handle = AudioEngine::Instance().Play(m_AudioClip);
			return;
		}

		Transform* p_transform = gameObject->GetTransfrom();
		if (p_transform == nullptr) {

			ENGINE_LOG_INFO("Audio Player attempted to play the audio {} as 3D audio on gameobject {}, however the gameobject has no transfrom component attached to it.", m_AudioClip->GetName(), gameObject->name);
			m_Handle = AudioEngine::Instance().Play(m_AudioClip);
			return;
		}

		m_Handle = AudioEngine::Instance().Play(m_AudioClip, p_transform);
		 

		
	}

	void AudioPlayer::Settings_UpdateAll()
	{
		Settings_SetLooping();
	}

	void AudioPlayer::Settings_SetLooping()
	{
		m_AudioClip->SetLooping(m_looped);
	}



}
