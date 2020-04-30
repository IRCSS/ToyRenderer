#pragma once
#include "Core.h"
#include "vendor/glm/glm.hpp"
#include <iostream>


namespace ToyRenderer{
    class TOYRENDERER_API Vector3 {

	// PUBLIC ======================================================================================    
	public: 
    
    	 Vector3();
       	 Vector3(float x, float y, float z);
    	~Vector3();
    
    	
    	Vector3 normalized() const;
        float   magnitude()  const;
    
    
    	// STATIC
    
    	static Vector3 Normalize(const Vector3& toNormalize);
    	static Vector3 Cross    (const Vector3& lhs, const Vector3& rhs);
    	static Vector3 Lerp     (const Vector3& a,   const Vector3& b, float t);
    	static float   Dot      (const Vector3& lhs, const Vector3& rhs);
    	static float   Distance (const Vector3& v0,  const Vector3 v1);
    
    	
    
    	
    	// OPERATOR
    
    	Vector3        operator= (const Vector3& toSet);
    	Vector3        operator+ (const Vector3& vec)  const;
    	void           operator+=(const Vector3& vec);
    	void           operator-=(const Vector3& vec);
    	void           operator*=(float rhs);
    
    	TOYRENDERER_API friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
    	TOYRENDERER_API friend Vector3 operator*(const Vector3& lhs, float rhs);
    	TOYRENDERER_API friend Vector3 operator*(float lhs, const Vector3& rhs);
    
		TOYRENDERER_API friend std::ostream& operator<<(std::ostream& os, const Vector3& rhs);
    	                                                                       
    																	       
    
    public:
    	float    x;
    	float    y;
    	float    z;
    
    	glm::vec3 v; // I dont actually want to have glm in the header file. Search for a better solution later
    
	// ______________________________________________________________________________________________
	// PRIVATE ======================================================================================    
    	
    private:
    	
    	float CalculateMag() const;
    	static float lerpf(float a, float b, float t);
    
    };
}

const static ToyRenderer::Vector3 vector3_zero   (ToyRenderer::Vector3(0.0f, 0.0f, 0.0f));
const static ToyRenderer::Vector3 vector3_one    (ToyRenderer::Vector3(1.0f, 1.0f, 1.0f));
const static ToyRenderer::Vector3 vector3_forward(ToyRenderer::Vector3(0.0f, 0.0f, 1.0f));
const static ToyRenderer::Vector3 vector3_right  (ToyRenderer::Vector3(1.0f, 0.0f, 0.0f));
const static ToyRenderer::Vector3 vector3_up     (ToyRenderer::Vector3(0.0f, 1.0f, 0.0f));

