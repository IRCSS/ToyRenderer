#pragma once



class Vector3 {

public:
	// READ ONLY 
	const float&    x;
	const float&    y;
	const float&    z;
	const float&    magnitude;

	
private:
	float   _x;
	float   _y;
	float   _z;
	float   _magnitude;

public: 

   	 Vector3(float x, float y, float z);
	~Vector3();




	// STATIC

	Vector3 Normalize(const Vector3& toNormalize)               const;
	Vector3 Cross(const Vector3& lfs, const Vector3& rhs)       const;
	Vector3 Lerp(const Vector3& a, const Vector3& b, float t)   const;
	/// Projects c1 on to c0, returns the e vector of projection c1-x normalized
	Vector3 OrthoNomalize(const Vector3& c0, const Vector3& c1) const;
	float   Dot(const Vector3& lfs, const Vector3& rhs)         const;
	float   Distance(const Vector3& v0, const Vector3 v1)       const;
	
	// OPERATOR

	Vector3& operator+=(const Vector3& vec) const;
	Vector3& operator+(const Vector3& vec)  const;
	Vector3& operator-=(const Vector3& vec) const;
	Vector3& operator-(const Vector3& vec)  const;

	
private:
	
};


const static Vector3 vector3_zero   (Vector3(0.0f, 0.0f, 0.0f));
const static Vector3 vector3_one    (Vector3(1.0f, 1.0f, 1.0f));
const static Vector3 vector3_forward(Vector3(0.0f, 0.0f, 1.0f));
const static Vector3 vector3_right  (Vector3(1.0f, 0.0f, 0.0f));
const static Vector3 vector3_up     (Vector3(0.0f, 1.0f, 0.0f));

