#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
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
		Matrix4x4  toReturn = Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
			                            0.0f, 1.0f, 0.0f, 0.0f,
			                            0.0f, 0.0f, 1.0f, 0.0f,
			                            0.0f, 0.0f, 0.0f, 1.0f);
	
		// TRS Matrix creation

		// scale
	    toReturn =   Matrix4x4(scale.x,      0.0f,       0.0f, 0.0f,
		 	                      0.0f,   scale.y,       0.0f, 0.0f,
		 	                      0.0f,      0.0f,    scale.z, 0.0f,
		 	                      0.0f,      0.0f,       0.0f, 1.0f) * toReturn;

		// rotate
		toReturn = GetRotationMatFromEuler(eulerRotaiton.x, eulerRotaiton.y, eulerRotaiton.z) *toReturn;

		// last translate 
		toReturn =    Matrix4x4(1.0f,             0.0f,       0.0f, position.x,
			                    0.0f,             1.0f,       0.0f, position.y,
			                    0.0f,             0.0f,       1.0f, position.z,
			                    0.0f,             0.0f,       0.0f,       1.0f) * toReturn;

		
		return toReturn;
	}

	Matrix4x4 Transform::worldToLocal() const
	{
		bool hasInverse;
		return localToWorld().Inverse(hasInverse);
	}

	Vector3 Transform::Foward() const
	{

		Matrix4x4 m = worldToLocal();
		Vector4 toReturn = m * Vector4(0.0, 0.0, 1.0, 0.0f);

		return Vector3(toReturn.x, toReturn.y, toReturn.z).normalized();
	}

	Vector3 Transform::Right() const
	{
		Matrix4x4 m = worldToLocal();
		Vector4 toReturn = m * Vector4(1.0, 0.0, 0.0, 0.0f);

		return Vector3(toReturn.x, toReturn.y, toReturn.z).normalized();
	}

	Vector3 Transform::Up() const
	{

		
		Matrix4x4 m = worldToLocal();
		Vector4 toReturn = m *Vector4(0.0, 1.0, 0.0, 0.0f);
		        

		return Vector3(toReturn.x, toReturn.y, toReturn.z).normalized();
	}

	/// rotation in radiance
	void Transform::RotateAroundOrigin(const Vector3 & axis, float theta)
	{

		glm::quat rotator = glm::quat(glm::vec3(eulerRotaiton.x, eulerRotaiton.y, eulerRotaiton.z));
		rotator = glm::rotate(rotator, theta, glm::vec3(axis.x, axis.y, axis.z));
		glm::vec3   euler = glm::eulerAngles(rotator);

		

		eulerRotaiton = Vector3(euler.x, euler.y, euler.z);

		

	}

	Matrix4x4 Transform::GetRotationMatFromEuler(float x, float y, float z) const
	{

		glm::mat4x4 toReturn = glm::yawPitchRoll(x, y, z);
		toReturn = glm::eulerAngleXYZ(x, y, z);
		return Matrix4x4(toReturn);

		//// euler to Matrix Rotation
		//float cos_x = cos(eulerRotaiton.x);
		//float sin_x = sin(eulerRotaiton.x);

		//float cos_y = cos(eulerRotaiton.y);
		//float sin_y = sin(eulerRotaiton.y);

		//float cos_z = cos(eulerRotaiton.z);
		//float sin_z = sin(eulerRotaiton.z);

		//// ---------- Ry*Rx*Rz
	 //   //Rz	
		//Matrix4x4   toReturn =   Matrix4x4(  cos_z,  -sin_z,   0.0f, 0.0f,
		//	                                 sin_z,   cos_z,   0.0f, 0.0f,
		//	                                  0.0f,    0.0f,   1.0f, 0.0f,
		//	                                  0.0f,    0.0f,   0.0f, 1.0f);

		////Rx
		//            toReturn =   Matrix4x4(   1.0f,    0.0f,   0.0f, 0.0f,
		//	                                  0.0f,   cos_x, -sin_x, 0.0f,
		//	                                  0.0f,   sin_x,  cos_x, 0.0f,
		//	                                  0.0f,    0.0f,   0.0f, 1.0f) * toReturn;
  //      //Ry	
		//            toReturn =   Matrix4x4(  cos_y,    0.0f,  sin_y, 0.0f,
		//            	                      0.0f,    1.0f,   0.0f, 0.0f,
		//            	                    -sin_y,    0.0f,  cos_y, 0.0f,
		//            	                      0.0f,    0.0f,   0.0f, 1.0f) * toReturn;
		//            
		//return toReturn;
	}

}


