#pragma once
#include "Core.h"
#include "vendor/glm/glm.hpp"
#include <iostream>

namespace ToyRenderer{

    class TOYRENDERER_API Vector2 {
    
    	// PUBLIC ======================================================================================
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
        	                                                                       
        																	       
        
        public:
        	float    x;
        	float    y;
        
        	glm::vec2 v; // I dont actually want to have glm in the header file. Search for a better solution later
        
    	// ______________________________________________________________________________________________
    	// PRIVATE ======================================================================================
    
        private:
        	
        	float CalculateMag() const;
        	static float lerpf(float a, float b, float t);
        
        };
    
}

const static ToyRenderer::Vector2 Vector2_zero   (ToyRenderer::Vector2(0.0f, 0.0f));
const static ToyRenderer::Vector2 Vector2_one    (ToyRenderer::Vector2(1.0f, 1.0f));
const static ToyRenderer::Vector2 Vector2_right  (ToyRenderer::Vector2(1.0f, 0.0f));
const static ToyRenderer::Vector2 Vector2_up     (ToyRenderer::Vector2(0.0f, 1.0f));

