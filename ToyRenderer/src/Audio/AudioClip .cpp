#include "AudioClip.h"

namespace ToyRenderer {
	AudioClip::AudioClip() : m_soLoudBackEndAudio(nullptr), m_AudioFileName(nullptr)
	{
	}

	AudioClip::AudioClip(SoLoud::Wav * backendsource) : m_soLoudBackEndAudio(backendsource), m_AudioFileName("")
	{
	}

	AudioClip ::~AudioClip()
	{
		delete m_soLoudBackEndAudio;
	}

	 SoLoud::Wav& AudioClip::GetBackEndAudioSourceHandel()
	{
		return *m_soLoudBackEndAudio;
	}

	void AudioClip::SetBackEndAudioHandel(SoLoud::Wav* toSet)
	{
		m_soLoudBackEndAudio = toSet;
	}

	void AudioClip::Name(const char * name)
	{
		m_AudioFileName = std::string(name);
	}

}