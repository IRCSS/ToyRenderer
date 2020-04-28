#include "TestClearColor.h"
#include "rendering/Renderer.h"
#include "vendor/imgui/imgui.h"
namespace test {
	TestClearColor::TestClearColor()
		: m_Color {0.6f, 0.1f, 0.5f, 1.0f}
	{
	}
	TestClearColor::~TestClearColor()
	{
	}
	void TestClearColor::OnUpdate(float deltaTime)
	{
	}
	void TestClearColor::OnRender()
	{
		GlCall(glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]));
		GlCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_Color);
	}
}