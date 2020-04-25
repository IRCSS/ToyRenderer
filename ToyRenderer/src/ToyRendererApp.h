#pragma once
#include "Core.h"

namespace ToyRenderer {

     class TOYRENDERER_API ToyRendererApp
     {
	     public: 
	  	   ToyRendererApp();
	  	   virtual ~ToyRendererApp();
	     
		   void Run();
     };

	 // Define in Client
	 ToyRendererApp* CreateApplication();
}

