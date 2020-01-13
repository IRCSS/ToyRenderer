#pragma once
#include "glm/glm.hpp"
#include <iostream>



class Vector4 {

public:
	// READ ONLY 
    float    x;
    float    y;
    float    z;
    float    w;

	
private:

	glm::vec4 v; // I dont actually want to have glm in the header file. Search for a better solution later

public: 

   	 Vector4(float x, float y, float z, float w);
	~Vector4();

	
	Vector4 normalized() const;
	float   magnitude()  const;


	// STATIC

	static Vector4 Normalize(const Vector4& toNormalize)            ;
	
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float t);
	static float   Dot(const Vector4& lhs, const Vector4& rhs)        ;
	static float   Distance(const Vector4& v0, const Vector4 v1)      ;
	
	// OPERATOR

	Vector4        operator=(const Vector4& toSet);
	Vector4        operator+(const Vector4& vec)  const;
	void           operator+=(const Vector4& vec);
	void           operator-=(const Vector4& vec);
	void           operator*=(float rhs);

	friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
	friend Vector4 operator*(const Vector4& lhs, float rhs);
	friend Vector4 operator*(float lhs, const Vector4& rhs);

    friend std::ostream& operator<<(std::ostream& os, Vector4 rhs); // if I pass on a Vector4& the complier gets confused in cases 
	                                                                // where the Vector4 is passed to the << stream by a function return
																	// find a better solution later

	
private:
	
	float CalculateMag() const;
	static float lerpf(float a, float b, float t);

};


const static Vector4 Vector4_zero   (Vector4(0.0f, 0.0f, 0.0f, 0.0f));
const static Vector4 Vector4_one    (Vector4(1.0f, 1.0f, 1.0f, 0.0f));
const static Vector4 Vector4_forward(Vector4(0.0f, 0.0f, 1.0f, 0.0f));
const static Vector4 Vector4_right  (Vector4(1.0f, 0.0f, 0.0f, 0.0f));
const static Vector4 Vector4_up     (Vector4(0.0f, 1.0f, 0.0f, 0.0f));

