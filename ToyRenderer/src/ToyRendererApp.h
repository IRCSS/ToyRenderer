#pragma once
#include "Core.h"
#include "world/Scene.h"

namespace ToyRenderer {

     class TOYRENDERER_API ToyRendererApp
     {
	     public: 
	  	   ToyRendererApp();
	  	   virtual ~ToyRendererApp();
	     
		   void Run();
     };

	 Scene* activeScene;

	 // Define in Client
	 ToyRendererApp* CreateApplication();

}

