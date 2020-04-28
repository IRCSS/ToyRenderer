#pragma once
#include "Core.h"
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "maths/Matrix4x4.h"
#include "Components/Component.h"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/quaternion.hpp"
#include "vendor/glm/gtx/euler_angles.hpp"


namespace ToyRenderer {

	class TOYRENDERER_API Transform : public Component {
    // PUBLIC ======================================================================================
	public:
		 Transform();
		~Transform();

		Transform(const Vector3 position, const Vector3 scale, const Vector3 Rotation);
		Matrix4x4 localToWorld() const;
		Matrix4x4 worldToLocal() const;
		
		Vector3   Foward()       const;
		Vector3   Right ()       const;
		Vector3   Up    ()       const;

		void RotateAroundOrigin(const Vector3& axis, float theta);
	
	public: 
		Vector3 position, scale;
		glm::fquat rotation;
    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================

	private:
		Matrix4x4 GetRotationMatFromEuler(float x, float y, float z) const;


	};

}