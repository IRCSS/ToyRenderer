#include "AudioClip .h"

namespace ToyRenderer {
	AudioClip::AudioClip() : m_soLoudBackEndAudio(nullptr)
	{
	}

	AudioClip::AudioClip(SoLoud::AudioSource * backendsource) : m_soLoudBackEndAudio(backendsource)
	{
	}

	AudioClip ::~AudioClip()
	{
		delete m_soLoudBackEndAudio;
	}

	SoLoud::AudioSource * AudioClip::GetBackEndAudioSourceHandel()
	{
		return m_soLoudBackEndAudio;
	}

	void AudioClip::SetBackEndAudioHandel(SoLoud::AudioSource* toSet)
	{
		m_soLoudBackEndAudio = toSet;
	}

}