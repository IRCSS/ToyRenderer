#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(const Vector4 & column1, const Vector4 & column2, const Vector4 & column3, const Vector4 & column4)
{
	glm::vec4 c1(column1.x, column1.y, column1.z, column1.w);
	glm::vec4 c2(column2.x, column2.y, column2.z, column2.w);
	glm::vec4 c3(column3.x, column3.y, column3.z, column3.w);
	glm::vec4 c4(column4.x, column4.y, column4.z, column4.w);

	m = glm::mat4x4(c1, c2, c3, c4);
}

/// Rows one after another. Row1, then Row2, then Row three 
Matrix4x4::Matrix4x4(const float i0j0, const float i0j1, const float i0j2, const float i0j3, // Row 1
	                 const float i1j0, const float i1j1, const float i1j2, const float i1j3, // Row 2
	                 const float i2j0, const float i2j1, const float i2j2, const float i2j3, // Row 3
	                 const float i3j0, const float i3j1, const float i3j2, const float i3j3) // Row 4
{

	m = glm::mat4x4(i0j0, i1j0, i2j0, i3j0,   // Column 1
	            	i0j1, i1j1, i2j1, i3j1,   // Column 2
		            i0j2, i1j2,	i2j2, i3j2,   // Column 3
	                i0j3, i1j3, i2j3, i3j3);  // Column 4

	// GLM uses directX memory layout  c1.x, c1.y, c.z, c2.x, c2.y, c.2z ...

}

Matrix4x4::Matrix4x4(glm::mat4x4 glmMat)
{
	m = glmMat;


}

Matrix4x4::Matrix4x4()
{
	m = glm::mat4x4(1, 0, 0,  0,
		            0, 1, 0,  0,
		            0, 0, 1,  0,
		            0, 0, 0,  1);
}

Matrix4x4::~Matrix4x4()
{
}

glm::mat4x4 Matrix4x4::GetGLM() const
{
	return m;
}

const Vector4 Matrix4x4::GetColumn(const int i) const
{
	return Vector4(m[i][0], m[i][1], m[i][2], m[i][3]);
}

const Vector4 Matrix4x4::GetRow(const int i) const
{
	return Vector4(m[0][i], m[1][i], m[2][i], m[3][i]);
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
	return Matrix4x4(m_inverse);
}

const Matrix4x4 Matrix4x4::Transpose() const
{
	glm::mat4x4 m_transposed =  glm::transpose(m);

	return Matrix4x4(m_transposed);
}

void Matrix4x4::operator=(const Matrix4x4 rhs)
{
	m = rhs.m;
}

std::ostream & operator<<(std::ostream & os, const Matrix4x4 rhs) 
{
	os << "{ " << rhs.GetRow(0) << ", " << rhs.GetRow(1) << ", " << rhs.GetRow(2) << "," << rhs.GetRow(3) << "}";
	return os;
}

Matrix4x4 operator*(const Matrix4x4 & lhs, const Matrix4x4 & rhs)
{
	glm::mat4x4 m_result = lhs.m * rhs.m;
	return Matrix4x4(m_result);
}

Vector4 operator*(const Matrix4x4 & lhs, const Vector4 & rhs)
{

   Vector4 toReturn = Vector4(Vector4::Dot(lhs.GetRow(0), rhs),
	                          Vector4::Dot(lhs.GetRow(1), rhs),
	                          Vector4::Dot(lhs.GetRow(2), rhs),
	                          Vector4::Dot(lhs.GetRow(3), rhs));
    return toReturn;
}
