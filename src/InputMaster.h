#pragma once
#include <gainput/gainput.h>
namespace ToyRenderer {
	enum Key {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, // Keyboard Keys
		LeftShift, RightShift, LeftCtrl, RightCtrl, LeftAlt, RightAlt, Space, Return, 
		LeftMouseButton, RightMouseButton, ArrowLeft, ArrowRight, ArrowUp, ArrowDown
	};

	class InputMaster {
	public: 

	private:
		gainput::InputManager  manager;
		gainput::InputMap*     map;
		gainput::DeviceId      MouseId;
		gainput::DeviceId      KeyboardId;

	public:
		 InputMaster();
		~InputMaster();

		void OnUpdate(float deltaTime);

		bool GetKeyDown(Key keycode);


	private:


	};
}