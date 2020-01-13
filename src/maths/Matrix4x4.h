#pragma once
#include "Vector4.h"
#include <iostream>
class Matrix4x4 {

private: 
	glm::mat4x4 m = glm::mat4x4(0.0f);
public: 
	Matrix4x4(const Vector4& column1, const Vector4& column2, const Vector4& column3, const Vector4& column4);
	Matrix4x4(const float i0j0, const float i0j1, const float i0j2, const float i0j3,
		      const float i1j0, const float i1j1, const float i1j2, const float i1j3, 
		      const float i2j0, const float i2j1, const float i2j2, const float i2j3, 
		      const float i3j0, const float i3j1, const float i3j2, const float i3j3);

	~Matrix4x4();


	const Vector4   GetColumn(const int i)   const;
	const Vector4   GetRow   (const int i)   const;
	const float     GetDeterminant()         const;
	const Matrix4x4 Inverse(bool& hasInverse)const;
	const Matrix4x4 Transpose()              const;

                void operator=(const Matrix4x4 rhs);
	friend Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);
	friend Vector4   operator*(const Matrix4x4& lhs, const Vector4& rhs);
	
	friend std::ostream&    operator<<(std::ostream& os, const Matrix4x4 rhs);


};