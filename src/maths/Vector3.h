#pragma once
#include "glm/glm.hpp"
#include <iostream>



class Vector3 {

public:
	float    x;
	float    y;
	float    z;

	glm::vec3 v; // I dont actually want to have glm in the header file. Search for a better solution later

public: 

   	 Vector3(float x, float y, float z);
	~Vector3();

	
	Vector3 normalized() const;
    float   magnitude()  const;


	// STATIC

	static Vector3 Normalize(const Vector3& toNormalize)            ;
	static Vector3 Cross(const Vector3& lhs, const Vector3& rhs)    ;
	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	static float   Dot(const Vector3& lhs, const Vector3& rhs)        ;
	static float   Distance(const Vector3& v0, const Vector3 v1)      ;

	

	
	// OPERATOR

	Vector3        operator=(const Vector3& toSet);
	Vector3        operator+(const Vector3& vec)  const;
	void           operator+=(const Vector3& vec);
	void           operator-=(const Vector3& vec);
	void           operator*=(float rhs);

	friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator*(const Vector3& lhs, float rhs);
	friend Vector3 operator*(float lhs, const Vector3& rhs);

    friend std::ostream& operator<<(std::ostream& os, Vector3 rhs); // if I pass on a Vector3& the complier gets confused in cases 
	                                                                // where the vector3 is passed to the << stream by a function return
																	// find a better solution later

	
private:
	
	float CalculateMag() const;
	static float lerpf(float a, float b, float t);

};


const static Vector3 vector3_zero   (Vector3(0.0f, 0.0f, 0.0f));
const static Vector3 vector3_one    (Vector3(1.0f, 1.0f, 1.0f));
const static Vector3 vector3_forward(Vector3(0.0f, 0.0f, 1.0f));
const static Vector3 vector3_right  (Vector3(1.0f, 0.0f, 0.0f));
const static Vector3 vector3_up     (Vector3(0.0f, 1.0f, 0.0f));

