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
