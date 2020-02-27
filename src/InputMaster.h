#pragma once
#include "GLFW/glfw3.h"
#include <unordered_map>
namespace ToyRenderer {

	enum KeyName {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, // Keyboard Keys
		LeftShift, RightShift, LeftCtrl, RightCtrl, LeftAlt, RightAlt, Space, Return,
		LeftMouseButton, RightMouseButton, ArrowLeft, ArrowRight, ArrowUp, ArrowDown
	};






	class InputMaster {

	public: 
		std::unordered_map<KeyName, int> keyMaping;
	private:
		GLFWwindow* p_window;

	public:
		 InputMaster(GLFWwindow* window);
		~InputMaster();

		void OnUpdate(float deltaTime);

		bool GetKeyDown(KeyName keycode);


	private:


	};
}