#pragma once
#include "Core.h"
#include <unordered_map>
namespace ToyRenderer {
	class AudioSource;
	class TOYRENDERER_API AudioAssembly {
	
    // PUBLIC ======================================================================================
	public:
		 AudioAssembly();
		~AudioAssembly();

		AudioSource* GetAudioSourceWitname(const char* AudioSourceTagName);

	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private: 
		#pragma warning( disable : 4251)  
	
		std::unordered_map<std::string, AudioSource*>         m_LoadedAudioSource;

		#pragma warning( default : 4251) // Turning the 4251 back on
	};

}