#pragma once
#include "Core.h"
#include <functional>
#include <vector>
#include "log/Log.h"

namespace ToyRenderer{
    namespace test {
    	class TOYRENDERER_API Test
    	{
		// PUBLIC ======================================================================================
		public: 
    		Test() {};
    	    virtual ~Test() {}
    
    		virtual void OnUpdate(float deltaTime) {}
    		virtual void OnRender() {}
    		virtual void OnImGuiRender(){}
    	};
    
    
    	class TOYRENDERER_API TestMenu : public Test {
		// PUBLIC ======================================================================================   	
		public: 
    		TestMenu(Test*& currentTestPointer);
    		
    
    		 void OnImGuiRender() override;
    		 void OnRender() override;
    		 template<typename T>
    		 void RegisterTest(const std::string& name) {
    
    			ENGINE_LOG_TRACE("Test Registered: {}" ,name );
    			 m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
    		 };

		// ______________________________________________________________________________________________
		// PRIVATE ======================================================================================   
    	private:
    		Test*& m_CurrentTest;
    		 std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    	};
    }
}