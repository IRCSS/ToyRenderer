#include "Color.h"

namespace ToyRenderer{
	
	
	Color::Color(float red, float green, float blue) : m_red(red), m_green(green),m_blue(blue),m_alpha(1.0f)
	{
	}
	Color::Color(float red, float green, float blue, float alpha) : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha)
	{
	}
	Color::Color(): m_red(0), m_green(0), m_blue(0), m_alpha(0.0f)
	{
	}
}

