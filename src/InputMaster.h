#pragma once
#include "GLFW/glfw3.h"
#include <unordered_map>
namespace ToyRenderer {

	enum KeyName {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, // Keyboard Keys
		LeftShift, RightShift, LeftCtrl, RightCtrl, LeftAlt, RightAlt, Space, Return,
		LeftMouseButton, RightMouseButton, ArrowLeft, ArrowRight, ArrowUp, ArrowDown
	};


	struct PressedKey {

	public: 
		bool        actedOnThisFrame;
		GLFWwindow*	window;
		int         keyCode;
	private:
		
		int numberOfFramesActive;
	public:
		PressedKey();
		PressedKey(const PressedKey& copyFrom);
		PressedKey(GLFWwindow* pWindow, int keyCode);

		void IsPressed();
		void SetUpForRelease();
		bool IsReleased();

	private: 
		

	};



	class InputMaster {

	public: 
		static std::unordered_map<KeyName, int> keyMaping;

		static std::unordered_map<int, PressedKey> PressedKeys;
		static std::unordered_map<int, PressedKey> ReleasedKeys;
	private:
		GLFWwindow* p_window;

	public:
		 InputMaster(GLFWwindow* window);
		~InputMaster();

		void OnUpdate(float deltaTime);

		static bool GetKeyDown(KeyName keycode);
		static bool GetKeyUp  (KeyName keycode);
		static bool GetKey    (KeyName keycode);

		
	private:



	};
}