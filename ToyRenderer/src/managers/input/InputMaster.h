#pragma once
#include "Core.h"
#include "vendor/GLFW/glfw3.h"
#include "maths/Vector2.h"
#include <unordered_map>
namespace ToyRenderer {

	enum KeyName {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, // Keyboard Keys
		LeftShift, RightShift, LeftCtrl, RightCtrl, LeftAlt, RightAlt, Space, Return,
		LeftMouseButton, RightMouseButton, ArrowLeft, ArrowRight, ArrowUp, ArrowDown
	};


	struct TOYRENDERER_API PressedKey {

	// PUBLIC ======================================================================================
	public:
		PressedKey();
		PressedKey(const PressedKey& copyFrom);
		PressedKey(GLFWwindow* pWindow, int keyCode);

		void IsPressed();
		void SetUpForRelease();
		bool IsReleased();
	public: 
		bool        actedOnThisFrame;
		GLFWwindow*	window;
		int         keyCode;

    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private:
		
		int numberOfFramesActive;


	};

	class TOYRENDERER_API Mouse {
	// PUBLIC ======================================================================================	
	public: 

		Mouse();
		Mouse(GLFWwindow* window);
		void    Update();
		void    SetMouseVisible(bool b);
		Vector2 GetMouseDelta() const;
	public: 
		/// Screen space, from top left corner
		Vector2 mousePos;
    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
	private:
		Vector2 mouseDelta;
		GLFWwindow* window;

	};

	class TOYRENDERER_API InputMaster {
	// PUBLIC ======================================================================================
	public:
		 InputMaster(GLFWwindow* window);
		~InputMaster();

		void OnUpdate(float deltaTime);

		static bool GetKeyDown(KeyName keycode);
		static bool GetKeyUp  (KeyName keycode);
		static bool GetKey    (KeyName keycode);
    #pragma warning( disable : 4251)  
	public: 
		static std::unordered_map<KeyName, int> keyMaping;

		static std::unordered_map<int, PressedKey> PressedKeys;
		static std::unordered_map<int, PressedKey> ReleasedKeys;

		static Mouse mouse;

    #pragma warning(default:4251) 
	private:
		GLFWwindow* p_window;


	};
}