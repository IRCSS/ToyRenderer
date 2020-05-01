#pragma once
#include "Core.h"
#include "world/Scene.h"
#include "system/Window.h"
#include "world/Time.h"
#include "managers/input/InputMaster.h"

namespace ToyRenderer {

	

     class TOYRENDERER_API ToyRendererApp
     {
	     public: 
	  	   ToyRendererApp();
	  	   virtual ~ToyRendererApp();
	     
		   void Run();


	      Scene       *activeScene;
	      Window      *window;
		  Time        *timeHandler;
		  InputMaster *inputMaster;

	 };
	 // Define in Client
	 ToyRendererApp* CreateApplication();

}

