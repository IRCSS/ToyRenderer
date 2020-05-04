#pragma once
#include "Core.h"
namespace ToyRenderer {
	class AudioSource;
	class TOYRENDERER_API AudioAssembly {
	
	public:
		 AudioAssembly();
		~AudioAssembly();

		AudioSource* GetAudioSourceWitname(const char* AudioSourceTagName);

	
	};

}