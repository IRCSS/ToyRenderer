#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"
namespace ToyRenderer {
	Transform::Transform()
	{
	}

	Transform::~Transform()
	{
	}

	Transform::Transform(const Vector3 i_position, const Vector3 i_scale, const Vector3 i_EulerRotation) : position(i_position), scale(i_scale), eulerRotaiton(i_EulerRotation)
	{
	}

	Matrix4x4 Transform::localToWorld() const
	{
		// Start off with identity matrix
		glm::mat4x4 toReturn = glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
			                               0.0f, 1.0f, 0.0f, 0.0f,
			                               0.0f, 0.0f, 1.0f, 0.0f,
			                               0.0f, 0.0f, 0.0f, 1.0f);
	
		// TRS Matrix creation
		// scale
	    toReturn = glm::mat4x4(scale.x,      0.0f,       0.0f, 0.0f,
			                      0.0f,   scale.y,       0.0f, 0.0f,
			                      0.0f,      0.0f,    scale.z, 0.0f,
			                      0.0f,      0.0f,       0.0f, 1.0f) * toReturn;
		
		
		// euler to Matrix Rotation
		float cos_x = cos(eulerRotaiton.x);
		float sin_x = sin(eulerRotaiton.x);

		float cos_y = cos(eulerRotaiton.y);
		float sin_y = sin(eulerRotaiton.y);

		float cos_z = cos(eulerRotaiton.z);
		float sin_z = sin(eulerRotaiton.z);

		// ---------- Rz*Ry*Rx
		//Rx
        toReturn = glm::mat4x4(   1.0f,    0.0f,   0.0f, 0.0f,
			                      0.0f,   cos_x, -sin_x, 0.0f,
			                      0.0f,   sin_x,  cos_x, 0.0f,
			                      0.0f,    0.0f,   0.0f, 1.0f) * toReturn;
        //Ry	
		toReturn = glm::mat4x4(  cos_y,    0.0f,  sin_y, 0.0f,
			                      0.0f,    1.0f,   0.0f, 0.0f,
			                    -sin_y,    0.0f,  cos_y, 0.0f,
			                      0.0f,    0.0f,   0.0f, 1.0f) * toReturn;
		//Rz	
		toReturn = glm::mat4x4(  cos_z,  -sin_z,   0.0f, 0.0f,
			                     sin_z,   cos_z,   0.0f, 0.0f,
			                      0.0f,    0.0f,   1.0f, 0.0f,
			                      0.0f,    0.0f,   0.0f, 1.0f) * toReturn;
		
		
		// last translate 
		toReturn =  glm::mat4x4(1.0f,             0.0f,       0.0f, 0.0f,
			                    0.0f,             1.0f,       0.0f, 0.0f,
			                    0.0f,             0.0f,       1.0f, 0.0f,
			                    position.x, position.y, position.z, 1.0f) * toReturn;




		

		
		return Matrix4x4(toReturn);
	}

	Matrix4x4 Transform::worldToLocal() const
	{
		bool hasInverse;
		return localToWorld().Inverse(hasInverse);
	}

}


