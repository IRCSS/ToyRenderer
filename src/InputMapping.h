#pragma once
#define TOYRENDERER_GLFWMAPPING void MapKeys(std::unordered_map<KeyName, int>& keymapping) { \
	keymapping[KeyName::A]                = GLFW_KEY_A;               \
	keymapping[KeyName::S]                = GLFW_KEY_S;               \
	keymapping[KeyName::W]                = GLFW_KEY_W;               \
	keymapping[KeyName::E]                = GLFW_KEY_E;               \
	keymapping[KeyName::Z]                = GLFW_KEY_Z;               \
	keymapping[KeyName::Q]                = GLFW_KEY_Q;               \
    keymapping[KeyName::LeftShift]        = GLFW_KEY_LEFT_SHIFT;      \
    keymapping[KeyName::RightMouseButton] = GLFW_MOUSE_BUTTON_RIGHT;  \
}; \
