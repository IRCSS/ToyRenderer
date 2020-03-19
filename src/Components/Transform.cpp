#include "Transform.h"

namespace ToyRenderer {
	Transform::Transform()
	{
	}

	Transform::~Transform()
	{
	}

	Transform::Transform(const Vector3 i_position, const Vector3 i_scale, const Vector3 i_EulerRotation) : position(i_position), scale(i_scale)
	{
		
		
		glm::quat qPitch = glm::angleAxis(glm::radians(i_EulerRotation.x), glm::vec3(1, 0, 0));
		glm::quat qYaw   = glm::angleAxis(glm::radians(i_EulerRotation.y), glm::vec3(0, 1, 0));
		glm::quat qRoll  = glm::angleAxis(glm::radians(i_EulerRotation.z), glm::vec3(0, 0, 1));

		
		rotation = qPitch * qYaw * qRoll;
		
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
		glm::mat4x4 r = glm::mat4_cast(rotation);
		toReturn = Matrix4x4(r) * toReturn;
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
		Vector4 v = localToWorld().GetColumn(2);
		return Vector3(v.x, v.y, v.z);
	}

	Vector3 Transform::Right() const
	{
		Vector4 v = localToWorld().GetColumn(0);
		return Vector3(v.x, v.y, v.z);
	}

	Vector3 Transform::Up() const
	{
		Vector4 v = localToWorld().GetColumn(1);
		return Vector3(v.x,v.y,v.z);
	}

	/// rotation in radiance
	void Transform::RotateAroundOrigin(const Vector3 & axis, float theta)
	{

		glm::fquat rotator = glm::fquat(1.0, 0.0,0.0,0.0);
		          rotator = glm::rotate(rotator, theta, glm::vec3(axis.x, axis.y, axis.z));
				  rotation = rotator* rotation ;
	}

	Matrix4x4 Transform::GetRotationMatFromEuler(float x, float y, float z) const
	{

		glm::mat4x4 toReturn = glm::eulerAngleXYZ(x, y, z);
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


