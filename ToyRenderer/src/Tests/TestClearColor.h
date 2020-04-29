#pragma once
#include "Core.h"
#include "Test.h"

namespace ToyRenderer{
    namespace test {
    	class TOYRENDERER_API TestClearColor : public Test {

		// PUBLIC ======================================================================================
		public: 
    		 TestClearColor();
    		~TestClearColor();
    
    		void OnUpdate(float deltaTime) override;
    		void OnRender()                override;
    		void OnImGuiRender()           override;

		// ______________________________________________________________________________________________
		// PRIVATE ======================================================================================    
    	private:
    		float m_Color[4];
    	};
    }
}