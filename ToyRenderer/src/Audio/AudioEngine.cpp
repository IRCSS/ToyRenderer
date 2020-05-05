#include "AudioEngine.h"

namespace ToyRenderer {

	AudioEngine* AudioEngine::m_pSingelton = nullptr;

   	AudioEngine::AudioEngine() 
   	{

   	}

	AudioEngine::~AudioEngine()
	{
	}

	void AudioEngine::Play(AudioClip  * toPlay)
	{
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
