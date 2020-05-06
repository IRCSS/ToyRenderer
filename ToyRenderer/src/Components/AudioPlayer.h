#pragma once
#include "Core.h"
#include "Components/Component.h"
#include "Audio/AudioClip.h"

namespace ToyRenderer {

	class TOYRENDERER_API AudioPlayer : public Component {

	// PUBLIC ======================================================================================
	public: 
		AudioPlayer();
		AudioPlayer(const char* AudioSourceTagName, bool looped = false, bool autoPlay = false);
		~AudioPlayer();

		void OnUpdate(float deltaTime) override;
		//void OnRender()                override;
		//void OnImGuiRender()           override;

		void Play();
		

	public:
		// Owmner ship is with the AudioAssembly. 
		AudioClip *     m_AudioClip;
		bool            m_looped;
		bool            m_autoPlayer;

		//TODO
		// bool m_3d
	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private:
		void Settings_UpdateAll();
		void Settings_SetLooping();

	};

}