#include "Vector3.h"




Vector3::Vector3( float x_,  float y_,  float z_) : x(_x), y(_y), z(_z), _x(x_), _y(y_), _z(z_),magnitude(_magnitude)
{
	v = glm::vec3(_x, _y, _z);
	_magnitude = CalculateMag();
}

Vector3::~Vector3()
{
}

Vector3 Vector3::normalized() const
{
	return Vector3::Normalize(*this);
}

Vector3 Vector3::Normalize(const Vector3 & toNormalize)
{
	glm::vec3 v = glm::vec3(toNormalize.x, toNormalize.y, toNormalize.z);
	glm::vec3 v_normalized = glm::normalize(v);
	return Vector3(v_normalized.x, v_normalized.y, v_normalized.z);

}

Vector3 Vector3::Cross(const Vector3 & lhs, const Vector3 & rhs)
{
	glm::vec3 v_lhs = glm::vec3(lhs.x, lhs.y, lhs.z);
	glm::vec3 v_rhs = glm::vec3(rhs.x, rhs.y, rhs.z);
	v_lhs = glm::cross(v_lhs, v_rhs);

	return Vector3(v_lhs.x, v_lhs.y, v_lhs.z);
}

Vector3 Vector3::Lerp(const Vector3 & a, const Vector3 & b, float t)
{
	float x = lerpf(a.x, b.x, t);
	float y = lerpf(a.y, b.y, t);
	float z = lerpf(a.z, b.z, t);
	return Vector3(x,y,z);
}

float Vector3::Dot(const Vector3 & lhs, const Vector3 & rhs)
{
	return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

float Vector3::Distance(const Vector3 & v0, const Vector3 v1)
{
	return (v0 - v1).magnitude;
}

Vector3 Vector3::operator=(const Vector3 & toSet)
{
	_x = toSet.x;
	_y = toSet.y;
	_z = toSet.z;

	v = glm::vec3(_x, _y, _z);
	_magnitude = CalculateMag();

	return Vector3(toSet.x, toSet.y, toSet.z);
}

Vector3 Vector3::operator+(const Vector3 & vec) const
{
	float x = _x + vec.x;
	float y = _y + vec.y;
	float z = _z + vec.z;

	return Vector3(x, y, z);
}


void Vector3::operator+=(const Vector3 & vec)
{
	 _x = _x + vec.x;
	 _y = _y + vec.y;
	 _z = _z + vec.z;

	 v = glm::vec3(_x, _y, _z);
	 _magnitude = CalculateMag();
}

void  Vector3::operator-=(const Vector3 & vec)
{
	_x  = _x - vec.x;
	_y  = _y - vec.y;
	_z  = _z - vec.z;

	v = glm::vec3(_x, _y, _z);
	_magnitude = CalculateMag();
	
}

void Vector3::operator*=(float rhs)
{
	_x = _x * rhs;
	_y = _y * rhs;
	_z = _z * rhs;

	v = glm::vec3(_x, _y, _z);
	_magnitude = CalculateMag();
}




Vector3 operator-(const Vector3 & lhs, const Vector3 & rhs)
{
	float x = lhs.x - rhs.x;
	float y = lhs.y - rhs.y;
	float z = lhs.z - rhs.z;

	return Vector3(x,y,z);
}

Vector3 operator*(const Vector3 & lhs, float rhs)
{
	return Vector3(lhs.x*rhs, lhs.y*rhs, lhs.z*rhs);
}

Vector3 operator*(float lhs, const Vector3 & rhs)
{
     return Vector3(rhs.x*lhs, rhs.y*lhs, rhs.z*lhs);;
}

std::ostream & operator<<(std::ostream& os, Vector3 rhs)
{
	os << " (" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
	return os;
}

float Vector3::CalculateMag() const
{
	return glm::length(v);
}

float Vector3::lerpf(float a, float b, float t)
{
	return glm::clamp(glm::mix(a, b, t), 0.0f, 1.0f);
}
