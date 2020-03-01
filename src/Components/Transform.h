#pragma once
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "maths/Matrix4x4.h"

namespace ToyRenderer {

	class Transform {

	public: 
		Vector3 position, scale, eulerRotaiton;

	private:

	public:
		 Transform();
		~Transform();

		Transform(const Vector3 position, const Vector3 scale, const Vector3 Rotation);
		Matrix4x4 localToWorld() const;
		Matrix4x4 worldToLocal() const;


	private:


	};

}