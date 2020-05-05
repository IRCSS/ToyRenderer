#pragma once
#include "Core.h"


namespace ToyRenderer {
	class AudioClip;
	class TOYRENDERER_API AudioEngine {
		   // PUBLIC ======================================================================================
	       public: 
		   
			    AudioEngine();
			   ~AudioEngine();
		       void Play(AudioClip * toPlay);
		       
		       
	           static AudioEngine& Instance();
			   static void Clear();
	      public: 

		  // ______________________________________________________________________________________________
		  // PRIVATE ======================================================================================
	      private:
		  static AudioEngine*  m_pSingelton;
	};
}