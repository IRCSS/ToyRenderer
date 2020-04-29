#include "Test.h"
#include "vendor/imgui/imgui.h"
#include "rendering/Renderer.h"

namespace ToyRenderer{
    namespace test {
    	TestMenu::TestMenu(Test*& currentTestPointer)
    		: m_CurrentTest(currentTestPointer)
    	{
    
    		
    	}
    	void TestMenu::OnImGuiRender()
    	{
    		for (auto& test : m_Tests) {
    			if (ImGui::Button(test.first.c_str()))
    				m_CurrentTest = test.second();
    		}
    
    	}
    	void TestMenu::OnRender()
    	{
    		glDepthMask(GL_TRUE);
    		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    		GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    	}
    }
}