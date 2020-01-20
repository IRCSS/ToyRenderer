#pragma once
#include "maths/Vector3.h"
namespace ToyRenderer {
	class Bounds {

	public: 
		Vector3 center;
		Vector3 extend;

	public:

		Bounds();
		Bounds(const Vector3& center, const Vector3& extend);


	};
}