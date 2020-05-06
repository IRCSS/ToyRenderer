#pragma once
#include "Core.h"
#include "Components/Component.h"
namespace ToyRenderer {
	class Transform;
	class TOYRENDERER_API AudioListner : public Component{

		// PUBLIC ======================================================================================
		public: 
			AudioListner();
			~AudioListner();

			void OnStart()                 override;
			void OnUpdate(float deltaTime) override;
		  //void OnRender()                override;
		  //void OnImGuiRender()           override;

		private:
			Transform* m_transform;
	};

}