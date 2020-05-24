#pragma once
#include "Core.h"
#include <unordered_map>
namespace ToyRenderer {
	class AudioClip;
	class TOYRENDERER_API AudioAssembly {
	
    // PUBLIC ======================================================================================
	public:
		 AudioAssembly();
		~AudioAssembly();

		AudioClip * GetAudioClipWitname(const char* AudioSourceTagName);

		bool LoadAudioInPath(const std::string& path);
		bool LoadAllAudiosInFolder(const std::string& path);

	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private: 
		#pragma warning( disable : 4251)  
	
		std::unordered_map<std::string, AudioClip *>         m_LoadedAudioSource;

		#pragma warning( default : 4251) // Turning the 4251 back on
	};

}