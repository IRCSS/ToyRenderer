#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
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

	Matrix4x4 Transform::worldToLocal() const
	{
		// Start off with identity matrix
		glm::mat4x4 toReturn = glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
			                               0.0f, 1.0f, 0.0f, 0.0f,
			                               0.0f, 0.0f, 1.0f, 0.0f,
			                               0.0f, 0.0f, 0.0f, 1.0f);
	
		// TRS Matrix creation

		// last translate 
		toReturn =  glm::mat4x4(1.0f,             0.0f,       0.0f, 0.0f,
			                    0.0f,             1.0f,       0.0f, 0.0f,
			                    0.0f,             0.0f,       1.0f, 0.0f,
			                    position.x, position.y, position.z, 1.0f) * toReturn;
		
		
		
		toReturn = GetRotationMatFromEuler(eulerRotaiton.x, eulerRotaiton.y, eulerRotaiton.z).GetGLM() *toReturn;
      
		

		// scale
	    toReturn = glm::mat4x4(scale.x,      0.0f,       0.0f, 0.0f,
			                      0.0f,   scale.y,       0.0f, 0.0f,
			                      0.0f,      0.0f,    scale.z, 0.0f,
			                      0.0f,      0.0f,       0.0f, 1.0f) * toReturn;

		
		return Matrix4x4(toReturn);
	}

	Matrix4x4 Transform::localToWorld() const
	{
		bool hasInverse;
		return worldToLocal().Inverse(hasInverse);
	}

	Vector3 Transform::Foward() const
	{
		Vector4 toReturn = localToWorld().GetColumn(2);

		return Vector3(toReturn.x, toReturn.y, toReturn.z).normalized();
	}

	Vector3 Transform::Right() const
	{
		Vector4 toReturn = localToWorld().GetColumn(0);

		return Vector3(toReturn.x, toReturn.y, toReturn.z).normalized();
	}

	Vector3 Transform::Up() const
	{
		Vector4 toReturn = localToWorld().GetColumn(1);

		return Vector3(toReturn.x, toReturn.y, toReturn.z).normalized();
	}

	/// rotation in radiance
	void Transform::RotateAroundOrigin(const Vector3 & axis, float theta)
	{
		
		glm::mat4x4 newLocaltoWorld = localToWorld().GetGLM();
		            newLocaltoWorld = glm::rotate(newLocaltoWorld, theta, glm::vec3(axis.x, axis.y,axis.z));
					
		glm::vec3   euler           = glm::eulerAngles( glm::quat_cast(newLocaltoWorld));


		eulerRotaiton = Vector3(euler.x, euler.y, euler.z);

	}

	Matrix4x4 Transform::GetRotationMatFromEuler(float x, float y, float z) const
	{

		// euler to Matrix Rotation
		float cos_x = cos(eulerRotaiton.x);
		float sin_x = sin(eulerRotaiton.x);

		float cos_y = cos(eulerRotaiton.y);
		float sin_y = sin(eulerRotaiton.y);

		float cos_z = cos(eulerRotaiton.z);
		float sin_z = sin(eulerRotaiton.z);

		// ---------- Rz*Ry*Rx
		//Rx
		glm::mat4x4 toReturn = glm::mat4x4(   1.0f,    0.0f,   0.0f, 0.0f,
			                                  0.0f,   cos_x, -sin_x, 0.0f,
			                                  0.0f,   sin_x,  cos_x, 0.0f,
			                                  0.0f,    0.0f,   0.0f, 1.0f);
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
		
		

		return Matrix4x4(toReturn);
	}

}


