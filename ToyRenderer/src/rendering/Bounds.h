#pragma once
#include "Core.h"
#include "maths/Vector3.h"

namespace ToyRenderer {
	class TOYRENDERER_API Bounds {

	// PUBLIC ======================================================================================	
	public:

		Bounds();
		Bounds(const Vector3& center, const Vector3& extend);

	public: 
		Vector3 center;
		Vector3 extend;



	};
}