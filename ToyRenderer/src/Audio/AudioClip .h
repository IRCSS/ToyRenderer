#pragma once
#include "Core.h"

namespace SoLoud {
	class AudioSource;
}

namespace ToyRenderer {

	class TOYRENDERER_API AudioClip {
	public:
		AudioClip();
		AudioClip(SoLoud::AudioSource* backendsource);
		~AudioClip();

		/// Get the backend format for the audio engine to play the sound. 
		SoLoud::AudioSource* GetBackEndAudioSourceHandel();
		void                 SetBackEndAudioHandel(SoLoud::AudioSource* toSet);

	private: 
		// Ownder ship is with this class, however it is created by the AudioAssembly
		SoLoud::AudioSource* m_soLoudBackEndAudio;

	};

}