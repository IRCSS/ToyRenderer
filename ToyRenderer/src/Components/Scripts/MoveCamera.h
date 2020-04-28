#pragma once
#include "Core.h"
#include "Components/Scripts/Script.h"
#include "Components/Transform.h"
namespace ToyRenderer
{ 
    namespace Behaviours {
    
    	class TOYRENDERER_API MoveCamera :public Script {

        // PUBLIC ======================================================================================

    	public:
    		MoveCamera();
    		MoveCamera( ToyRenderer::Transform* cam);
    		virtual ~MoveCamera();
    
    		virtual void OnUpdate(float deltaTime);
    	public: 
    		ToyRenderer::Transform* m_cam;

    		float movementSpeed   = 0.01f;
    		float rotationSpeed   = 0.005f;
    		float speedMultiplyer = 3.0f;
    
    	};
    
    }

}