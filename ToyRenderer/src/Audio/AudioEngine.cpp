#include "AudioEngine.h"
#include "vendor/soloud/soloud.h"
#include "Audio/AudioClip.h"
#include "vendor/soloud/soloud_wav.h"
#include "Components/Transform.h"
#include "log/Log.h"
namespace ToyRenderer {

	AudioEngine* AudioEngine::m_pSingelton = nullptr;

   	AudioEngine::AudioEngine() : m_soLoudBackend(nullptr)
   	{

		SoLoud::Soloud::FLAGS flags = static_cast<SoLoud::Soloud::FLAGS>(static_cast<int>(SoLoud::Soloud::FLAGS::CLIP_ROUNDOFF) | static_cast<int>(SoLoud::Soloud::FLAGS::LEFT_HANDED_3D));

		m_soLoudBackend = new SoLoud::Soloud; // object created
		m_soLoudBackend->init(flags);         // back-end initialization
		
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

	int AudioEngine::Play(AudioClip* toPlay)
	{
		return m_soLoudBackend->play(toPlay->GetBackEndAudioSourceHandel());
	}

	int AudioEngine::Play(AudioClip * toPlay, const Transform * transform)
	{
		int handel = m_soLoudBackend->play3d(toPlay->GetBackEndAudioSourceHandel(), transform->position.x, transform->position.y, transform->position.z);

		m_soLoudBackend->set3dSourceAttenuation(handel, 1, 1);

		return handel;
	}

	void AudioEngine::SetAudioListner(const Transform * listnerTransform)
	{
		m_soLoudBackend->set3dListenerPosition(listnerTransform->position.x  , listnerTransform->position.y  , listnerTransform->position.z  ); 
		m_soLoudBackend->set3dListenerAt      (listnerTransform->Foward().x  , listnerTransform->Foward().y  , listnerTransform->Foward().z  );
		m_soLoudBackend->set3dListenerUp      (listnerTransform->Up().x      , listnerTransform->Up().y      , listnerTransform->Up().z      );
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
