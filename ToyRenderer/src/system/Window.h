#pragma once
#include "Core.h"
#include "vendor/GLFW/glfw3.h"

namespace ToyRenderer {

	class TOYRENDERER_API Window {

	// PUBLIC ======================================================================================
	public: 

		 Window();
		~Window();

		void SetContextAsCurrent();
		GLFWwindow* GetWindowAddress();

	public:
		static int Width;
		static int Height;

    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================

	private:
		const int contextVersionMin = 3;
		const int contextVersionMax = 4;



        #pragma warning( disable : 4251)  
		// std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. Private stuff wont be inlined so I will disable them
		GLFWwindow* p_Window;
	    #pragma warning(default:4251) // Turning the 4251 back on		

	};

}