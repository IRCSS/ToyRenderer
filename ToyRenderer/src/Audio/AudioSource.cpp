#include "AudioSource.h"

namespace ToyRenderer {
	AudioSource::AudioSource() : m_soLoudBackEndAudio(nullptr)
	{
	}

	AudioSource::AudioSource(SoLoud::AudioSource * backendsource) : m_soLoudBackEndAudio(backendsource)
	{
	}

	AudioSource::~AudioSource()
	{
		delete m_soLoudBackEndAudio;
	}

	SoLoud::AudioSource * AudioSource::GetBackEndAudioSourceHandel()
	{
		return m_soLoudBackEndAudio;
	}

	void AudioSource::SetBackEndAudioHandel(SoLoud::AudioSource* toSet)
	{
		m_soLoudBackEndAudio = toSet;
	}

}