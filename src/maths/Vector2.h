#pragma once
#include "glm/glm.hpp"
#include <iostream>



class Vector2 {

public:
	float    x;
	float    y;

	glm::vec2 v; // I dont actually want to have glm in the header file. Search for a better solution later

public: 

	 Vector2();
   	 Vector2(float x, float y);
	~Vector2();

	
	Vector2 normalized() const;
    float   magnitude()  const;


	// STATIC

	static Vector2 Normalize(const Vector2& toNormalize)              ;
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t)  ;
	static float   Dot(const Vector2& lhs, const Vector2& rhs)        ;
	static float   Distance(const Vector2& v0, const Vector2 v1)      ;

	

	
	// OPERATOR

	Vector2        operator=(const Vector2& toSet);
	Vector2        operator+(const Vector2& vec)  const;
	void           operator+=(const Vector2& vec);
	void           operator-=(const Vector2& vec);
	void           operator*=(float rhs);

	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator*(const Vector2& lhs, float rhs);
	friend Vector2 operator*(float lhs, const Vector2& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Vector2& rhs); 
	                                                                       
																	       

	
private:
	
	float CalculateMag() const;
	static float lerpf(float a, float b, float t);

};


const static Vector2 Vector2_zero   (Vector2(0.0f, 0.0f));
const static Vector2 Vector2_one    (Vector2(1.0f, 1.0f));
const static Vector2 Vector2_right  (Vector2(1.0f, 0.0f));
const static Vector2 Vector2_up     (Vector2(0.0f, 1.0f));

