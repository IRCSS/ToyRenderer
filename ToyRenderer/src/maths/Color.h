#pragma once
#include "Core.h"

namespace ToyRenderer{
	class TOYRENDERER_API Color {

	// PUBLIC ======================================================================================

	public:
		Color(float red, float green, float blue);
		Color(float red, float green, float blue, float alpha);
		Color();

	public:
		float m_red, m_green, m_blue, m_alpha;
	};
}