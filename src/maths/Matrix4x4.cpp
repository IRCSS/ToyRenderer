#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(const Vector4 & column1, const Vector4 & column2, const Vector4 & column3, const Vector4 & column4)
{
	glm::vec4 c1(column1.x, column1.y, column1.z, column1.w);
	glm::vec4 c2(column2.x, column2.y, column2.z, column2.w);
	glm::vec4 c3(column3.x, column3.y, column3.z, column3.w);
	glm::vec4 c4(column4.x, column4.y, column4.z, column4.w);

	m = glm::mat4x4(c1, c2, c3, c4);
}

Matrix4x4::Matrix4x4(const float i0j0, const float i0j1, const float i0j2, const float i0j3, 
	                 const float i1j0, const float i1j1, const float i1j2, const float i1j3,
	                 const float i2j0, const float i2j1, const float i2j2, const float i2j3, 
	                 const float i3j0, const float i3j1, const float i3j2, const float i3j3)
{

	m = glm::mat4x4(i0j0, i0j1, i0j2, i0j3,
	            	i1j0, i1j1, i1j2, i1j3,
		            i2j0, i2j1,	i2j2, i2j3,
	                i3j0, i3j1, i3j2, i3j3);

}

Matrix4x4::~Matrix4x4()
{
}

const Vector4 Matrix4x4::GetColumn(const int i) const
{
	return Vector4(m[0][i], m[1][i], m[2][i], m[3][i]);
}

const Vector4 Matrix4x4::GetRow(const int i) const
{
	return Vector4(m[i][0], m[i][1], m[i][2], m[i][3]);
}

const float Matrix4x4::GetDeterminant() const
{
	return glm::determinant(m);;
}

const Matrix4x4 Matrix4x4::Inverse(bool & hasInverse) const
{
	if (GetDeterminant() == 0) {
		hasInverse = false;
		return Matrix4x4(Vector4_zero, Vector4_zero, Vector4_zero, Vector4_zero);
	}

	glm::mat4x4 m_inverse = glm::inverse(m);
	return Matrix4x4(m_inverse[0][0], m_inverse[0][1], m_inverse[0][2], m_inverse[0][3],
		             m_inverse[1][0], m_inverse[1][1], m_inverse[1][2], m_inverse[1][3],
		             m_inverse[2][0], m_inverse[2][1], m_inverse[2][2], m_inverse[2][3],
		             m_inverse[3][0], m_inverse[3][1], m_inverse[3][2], m_inverse[3][3]);
}

const Matrix4x4 Matrix4x4::Transpose() const
{
	glm::mat4x4 m_transposed =  glm::transpose(m);

	return Matrix4x4(m_transposed[0][0], m_transposed[0][1], m_transposed[0][2], m_transposed[0][3],
					 m_transposed[1][0], m_transposed[1][1], m_transposed[1][2], m_transposed[1][3],
					 m_transposed[2][0], m_transposed[2][1], m_transposed[2][2], m_transposed[2][3],
					 m_transposed[3][0], m_transposed[3][1], m_transposed[3][2], m_transposed[3][3]);
}

void Matrix4x4::operator=(const Matrix4x4 rhs)
{
	Vector4 c1 = rhs.GetColumn(0);
	Vector4 c2 = rhs.GetColumn(1);
	Vector4 c3 = rhs.GetColumn(2);
	Vector4 c4 = rhs.GetColumn(3);

	m = glm::mat4x4(c1.x, c1.y, c1.z, c1.w,
		            c2.x, c2.y, c2.z, c2.w,
		            c3.x, c3.y, c3.z, c3.w,
		            c4.x, c4.y, c4.z, c4.w);
}

std::ostream & operator<<(std::ostream & os, const Matrix4x4 rhs) 
{
	os << "{ " << rhs.GetColumn(0) << ", " << rhs.GetColumn(1) << ", " << rhs.GetColumn(2) << "," << rhs.GetColumn(3) << "}";
	return os;
}

Matrix4x4 operator*(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
{
	glm::mat4x4 m_result = lhs.m * rhs.m;
	return Matrix4x4(m_result[0][0], m_result[0][1], m_result[0][2], m_result[0][3],
					 m_result[1][0], m_result[1][1], m_result[1][2], m_result[1][3],
					 m_result[2][0], m_result[2][1], m_result[2][2], m_result[2][3],
					 m_result[3][0], m_result[3][1], m_result[3][2], m_result[3][3]);
}

Vector4 operator*(const Matrix4x4 & lhs, const Vector4 & rhs)
{
	glm::vec4 v(rhs.x, rhs.y, rhs.z, rhs.w);
	v = lhs.m * v;
	return Vector4(v.x, v.y, v.z, v.w);
}
