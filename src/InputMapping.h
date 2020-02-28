#pragma once
#define TOYRENDERER_GLFWMAPPING void MapKeys(std::unordered_map<KeyName, int>& keymapping) { \
	keymapping[KeyName::A] = GLFW_KEY_A; \
	keymapping[KeyName::S] = GLFW_KEY_S; \
	keymapping[KeyName::W] = GLFW_KEY_W; \
	keymapping[KeyName::Z] = GLFW_KEY_Z; \
}; \
