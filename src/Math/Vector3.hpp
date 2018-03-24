/*
 * Vector3.hpp
 *
 *  Created on: 18.02.2016
 *      Author: Christoph Neuhauser
 */

#ifndef MATH_GEOMETRY_VECTOR3_HPP_
#define MATH_GEOMETRY_VECTOR3_HPP_

#include <cmath>

/**
 * Represents a 3D float vector.
 */
class Vector3
{
public:
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float _x, float _y) : x(_x), y(_y), z(1.0f) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	union {
		struct {
			float x;
			float y;
			float z;
		}; ///< Component access
		float c[3]; ///< Array access
	};

	// All operators behave exactly as expected
	bool operator ==(const Vector3 &rhs) const;
	void operator =(const Vector3 &rhs);
	void operator +=(const Vector3 &rhs);
	void operator -=(const Vector3 &rhs);
	void operator *=(const Vector3 &rhs);
	void operator /=(const Vector3 &rhs);
	void operator /=(const float &rhs) {x /= rhs; y /= rhs;}
	Vector3 operator +(const Vector3 &rhs) const;
	Vector3 operator -(const Vector3 &rhs) const;
	Vector3 operator *(const Vector3 &rhs) const;
	Vector3 operator /(const Vector3 &rhs) const;
	inline friend Vector3 operator -(const Vector3 &v) { return Vector3(-v.x, -v.y); }
	inline friend Vector3 operator *(const Vector3 &v, const float f) { return Vector3(v.x * f, v.y * f); }
	inline friend Vector3 operator /(const Vector3 &v, const float f) { return Vector3(v.x / f, v.y / f); }
	inline friend Vector3 operator *(const float f, const Vector3 &v) { return Vector3(v.x * f, v.y * f); }
	inline friend Vector3 operator /(const float f, const Vector3 &v) { return Vector3(v.x / f, v.y / f); }
	bool operator < (const Vector3 &rhs) const;
	bool operator <=(const Vector3 &rhs) const;
	bool operator > (const Vector3 &rhs) const;
	bool operator >=(const Vector3 &rhs) const;
	bool isApproximately(const Vector3 &other);

	/// Returns the positive angle between this vector and the passed one in the range of [0,pi]
	inline float   angle(const Vector3& v2) const { return acos((x * v2.x + y * v2.y + z * v2.z) / sqrt((x * x + y * y + z * z) * (v2.x * v2.x + v2.y * v2.y + v2.z * v2.z))); }
	/// Computes the length of the vector in the L2 norm
	inline float   length() const { return sqrt(x * x + y * y + z * z); }
	/// Computes the squared length (faster, as no square root is needed)
	inline float   lengthSquared() const { return x * x + y * y + z * z; }
	/**
	 * Assumption: The length of this vector is not approximately zero.
	 * @return: A copy of this vector with unit length.
	 */
	inline Vector3 normalized() const { return *this / sqrt(x * x + y * y + z * z); }
	/// Computes the cross product between this vector and the passed one
	inline Vector3 cross(const Vector3& v2) const { return Vector3(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x); }
	/// Computes the dot product between this vector and the passed one
	inline float   dot(const Vector3& v2) const { return x * v2.x + y * v2.y + z * v2.z; }

	/// Interpolates linearly between this vector and the passed one
	inline Vector3 interpolateLinear(const Vector3& v2, float percent) const { return *this + (v2 - *this) * percent; }
};

#endif /* MATH_GEOMETRY_VECTOR3_HPP_ */
