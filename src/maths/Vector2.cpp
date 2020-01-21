#include "Vector2.h"




Vector2::Vector2() : x(0), y(0)
{
	v = glm::vec2(x, y);
}

Vector2::Vector2( float x_,  float y_) : x(x_), y(y_)
{
	v = glm::vec2(x, y);
}

Vector2::~Vector2()
{
}

Vector2 Vector2::normalized() const
{
	return Vector2::Normalize(*this);
}

Vector2 Vector2::Normalize(const Vector2 & toNormalize)
{
	glm::vec2 v = glm::vec2(toNormalize.x, toNormalize.y);
	glm::vec2 v_normalized = glm::normalize(v);
	return Vector2(v_normalized.x, v_normalized.y);

}


Vector2 Vector2::Lerp(const Vector2 & a, const Vector2 & b, float t)
{
	float x = lerpf(a.x, b.x, t);
	float y = lerpf(a.y, b.y, t);
	return Vector2(x,y);
}

float Vector2::Dot(const Vector2 & lhs, const Vector2 & rhs)
{
	return lhs.x*rhs.x + lhs.y*rhs.y;
}

float Vector2::Distance(const Vector2 & v0, const Vector2 v1)
{
	return (v0 - v1).magnitude();
}

float Vector2::magnitude() const
{
	 return CalculateMag();

}

Vector2 Vector2::operator=(const Vector2 & toSet)
{
	x = toSet.x;
	y = toSet.y;

	v = glm::vec2(x, y);

	return Vector2(toSet.x, toSet.y);
}

Vector2 Vector2::operator+(const Vector2 & vec) const
{
	float _x = x + vec.x;
	float _y = y + vec.y;

	return Vector2(_x, _y);
}


void Vector2::operator+=(const Vector2 & vec)
{
	 x = x + vec.x;
	 y = y + vec.y;

	 v = glm::vec2(x, y);
}

void  Vector2::operator-=(const Vector2 & vec)
{
	x  = x - vec.x;
	y  = y - vec.y;
	

	v = glm::vec2(x, y);
	
}

void Vector2::operator*=(float rhs)
{
	x = x * rhs;
	y = y * rhs;
	

	v = glm::vec2(x, y);
}




Vector2 operator-(const Vector2 & lhs, const Vector2 & rhs)
{
	float x = lhs.x - rhs.x;
	float y = lhs.y - rhs.y;
	

	return Vector2(x,y);
}

Vector2 operator*(const Vector2 & lhs, float rhs)
{
	return Vector2(lhs.x*rhs, lhs.y*rhs);
}

Vector2 operator*(float lhs, const Vector2 & rhs)
{
     return Vector2(rhs.x*lhs, rhs.y*lhs);
}

std::ostream & operator<<(std::ostream& os, const Vector2& rhs)
{
	os << " (" << rhs.x << ", " << rhs.y << ")";
	return os;
}

float Vector2::CalculateMag() const
{
	return glm::length(v);
}

float Vector2::lerpf(float a, float b, float t)
{
	return glm::clamp(glm::mix(a, b, t), 0.0f, 1.0f);
}
