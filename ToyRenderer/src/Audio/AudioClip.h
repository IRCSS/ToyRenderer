#pragma once
#include "Core.h"
#include <string>
namespace SoLoud {
	class Wav;
}

namespace ToyRenderer {

	class TOYRENDERER_API AudioClip {
	public:
		AudioClip();
		AudioClip(SoLoud::Wav* backendsource);
		~AudioClip();

		/// Get the backend format for the audio engine to play the sound. 
	    SoLoud::Wav& GetBackEndAudioSourceHandel();
		void         SetBackEndAudioHandel(SoLoud::Wav* toSet);
		void         Name(const char* name);
		

	private: 
		// Ownder ship is with this class, however it is created by the AudioAssembly
		SoLoud::Wav* m_soLoudBackEndAudio;
		std::string  m_AudioFileName;
	};

}