#pragma once
#include "maths/Vector4.h"
#include "maths/Vector3.h"
#include "maths/Matrix4x4.h"
#include "Components/Component.h"


namespace ToyRenderer {

	class Transform : Component {

	public: 
		Vector3 position, scale, eulerRotaiton;

	private:

	public:
		 Transform();
		~Transform();

		Transform(const Vector3 position, const Vector3 scale, const Vector3 Rotation);
		Matrix4x4 localToWorld() const;
		Matrix4x4 worldToLocal() const;
		Vector3   Foward()       const;
		Vector3   Right ()       const;
		Vector3   Up    ()       const;


	private:


	};

}