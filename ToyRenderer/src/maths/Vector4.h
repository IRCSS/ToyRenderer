#pragma once
#include "Core.h"
#include "vendor/glm/glm.hpp"
#include <iostream>


namespace ToyRenderer {

    class TOYRENDERER_API Vector4 {

	// PUBLIC ======================================================================================

    public: 
    
    	 Vector4();
       	 Vector4(float x, float y, float z, float w);
    	~Vector4();
    
    	
    	Vector4 normalized() const;
    	float   magnitude()  const;
    
    
    	// STATIC
    
    	static Vector4 Normalize(const Vector4& toNormalize);
    	
    	static Vector4 Lerp     (const Vector4& a,   const Vector4& b, float t);
    	static float   Dot      (const Vector4& lhs, const Vector4& rhs);
    	static float   Distance (const Vector4& v0,  const Vector4  v1);
    	
    	// OPERATOR
    
    	Vector4        operator= (const Vector4& toSet);
    	Vector4        operator+ (const Vector4& vec)  const;
    	void           operator+=(const Vector4& vec);
    	void           operator-=(const Vector4& vec);
    	void           operator*=(float rhs);
    
    	friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
    	friend Vector4 operator*(const Vector4& lhs, float rhs);
    	friend Vector4 operator*(float lhs, const Vector4& rhs);
    
        friend std::ostream& operator<<(std::ostream& os, const Vector4& rhs); 
    	                                                                       
    public:
    	// READ ONLY 
        float    x;
        float    y;
        float    z;
        float    w;

    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================   

    private:
    	
    	float CalculateMag() const;
    	static float lerpf(float a, float b, float t);
    	
    private:
    
    	glm::vec4 v; // I dont actually want to have glm in the header file. Search for a better solution later
    
    																	       
    
    	
    
    };

}
const static ToyRenderer::Vector4 Vector4_zero   (ToyRenderer::Vector4(0.0f, 0.0f, 0.0f, 0.0f));
const static ToyRenderer::Vector4 Vector4_one    (ToyRenderer::Vector4(1.0f, 1.0f, 1.0f, 0.0f));
const static ToyRenderer::Vector4 Vector4_forward(ToyRenderer::Vector4(0.0f, 0.0f, 1.0f, 0.0f));
const static ToyRenderer::Vector4 Vector4_right  (ToyRenderer::Vector4(1.0f, 0.0f, 0.0f, 0.0f));
const static ToyRenderer::Vector4 Vector4_up     (ToyRenderer::Vector4(0.0f, 1.0f, 0.0f, 0.0f));

