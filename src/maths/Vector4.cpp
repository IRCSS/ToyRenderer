#include "Vector4.h"




Vector4::Vector4() : x(0), y(0), z(0), w(0)
{
	v = glm::vec4(x, y, z, w);
}

Vector4::Vector4( float x_,  float y_,  float z_, float w_) : x(x_), y(y_), z(z_), w(w_)
{
	v = glm::vec4(x, y, z, w);
}

Vector4::~Vector4()
{
}

Vector4 Vector4::normalized() const
{
	return Vector4::Normalize(*this);
}

float Vector4::magnitude() const
{

	return CalculateMag();
}

Vector4 Vector4::Normalize(const Vector4 & toNormalize)
{
	glm::vec4 v = glm::vec4(toNormalize.x, toNormalize.y, toNormalize.z, toNormalize.w);
	glm::vec4 v_normalized = glm::normalize(v);
	return Vector4(v_normalized.x, v_normalized.y, v_normalized.z, v_normalized.w);

}



Vector4 Vector4::Lerp(const Vector4 & a, const Vector4 & b, float t)
{
	float x = lerpf(a.x, b.x, t);
	float y = lerpf(a.y, b.y, t);
	float z = lerpf(a.z, b.z, t);
	float w = lerpf(a.w, b.w, t);
	return Vector4(x,y,z, w);
}

float Vector4::Dot(const Vector4 & lhs, const Vector4 & rhs)
{
	return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w * rhs.w;
}

float Vector4::Distance(const Vector4 & v0, const Vector4 v1)
{
	return (v0 - v1).magnitude();
}

Vector4 Vector4::operator=(const Vector4 & toSet)
{
	x = toSet.x;
	y = toSet.y;
	z = toSet.z;
	w = toSet.w;

	v = glm::vec4(x, y, z, w);

	return Vector4(toSet.x, toSet.y, toSet.z, toSet.w);
}

Vector4 Vector4::operator+(const Vector4 & vec) const
{
	float _x = x + vec.x;
	float _y = y + vec.y;
	float _z = z + vec.z;
	float _w = w + vec.w;

	return Vector4(_x, _y, _z, _w);
}


void Vector4::operator+=(const Vector4 & vec)
{
	 x = x + vec.x;
	 y = y + vec.y;
	 z = z + vec.z;
	 w = w + vec.w;

	 v = glm::vec4(x, y, z, w);

}

void  Vector4::operator-=(const Vector4 & vec)
{
	x  = x - vec.x;
	y  = y - vec.y;
	z  = z - vec.z;
	w  = w - vec.w;

	v = glm::vec4(x, y, z, w);
	
	
}

void Vector4::operator*=(float rhs)
{
	x = x * rhs;
	y = y * rhs;
	z = z * rhs;
	w = w * rhs;

	v = glm::vec4(x, y, z, w);
}




Vector4 operator-(const Vector4 & lhs, const Vector4 & rhs)
{
	float x = lhs.x - rhs.x;
	float y = lhs.y - rhs.y;
	float z = lhs.z - rhs.z;
	float w = lhs.w - rhs.w;

	return Vector4(x,y,z, w);
}

Vector4 operator*(const Vector4 & lhs, float rhs)
{
	return Vector4(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs, lhs.w*rhs);
}

Vector4 operator*(float lhs, const Vector4 & rhs)
{
     return Vector4(rhs.x*lhs, rhs.y*lhs, rhs.z*lhs, rhs.w * lhs);;
}

std::ostream & operator<<(std::ostream& os, const Vector4& rhs)
{
	os << " (" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", "<< rhs.w<< ")";
	return os;
}

float Vector4::CalculateMag() const
{
	return glm::length(v);
}

float Vector4::lerpf(float a, float b, float t)
{
	return glm::clamp(glm::mix(a, b, t), 0.0f, 1.0f);
}
