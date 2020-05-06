#pragma once
#include "Core.h"

namespace SoLoud {
	class Soloud;
}
namespace ToyRenderer {
	class AudioClip;
	class Transform;
	class TOYRENDERER_API AudioEngine {
		   // PUBLIC ======================================================================================
	       public: 
		   
			    AudioEngine();
			   ~AudioEngine();

			   void OnUpdate(float deltaTime);

		       void Play(AudioClip*  toPlay);
			   void Play(AudioClip* toPlay, const Transform* transfrom);
		       
			   void SetAudioListner(const Transform* listnerTransform);

	           static AudioEngine& Instance();
			   static void Clear();
	      public: 

		  // ______________________________________________________________________________________________
		  // PRIVATE ======================================================================================
	      private:
		  static AudioEngine*  m_pSingelton;

		      SoLoud::Soloud*  m_soLoudBackend;
	};
}