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
	glm::vec3 v_normalized = glm::normalize(v);
	return Vector3(v_normalized.x, v_normalized.y, v_normalized.z);
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
