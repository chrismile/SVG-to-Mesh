/*
 * Vector2.hpp
 *
 *  Created on: 10.01.2015
 *      Author: Christoph Neuhauser
 */

#ifndef MATH_VECTOR2_HPP_
#define MATH_VECTOR2_HPP_

#include <cmath>

/**
 * Represents a 2D float vector.
 */
class Vector2
{
public:
	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	float x, y;

	// All operators behave exactly as expected
	bool operator ==(const Vector2 &rhs) const;
	void operator =(const Vector2 &rhs);
	void operator +=(const Vector2 &rhs);
	void operator -=(const Vector2 &rhs);
	void operator *=(const Vector2 &rhs);
	void operator /=(const Vector2 &rhs);
	void operator /=(const float &rhs) {x /= rhs; y /= rhs;}
	Vector2 operator +(const Vector2 &rhs) const;
	Vector2 operator -(const Vector2 &rhs) const;
	Vector2 operator *(const Vector2 &rhs) const;
	Vector2 operator /(const Vector2 &rhs) const;
	inline friend Vector2 operator -(const Vector2 &v) { return Vector2(-v.x, -v.y); }
	inline friend Vector2 operator *(const Vector2 &v, const float f) { return Vector2(v.x * f, v.y * f); }
	inline friend Vector2 operator /(const Vector2 &v, const float f) { return Vector2(v.x / f, v.y / f); }
	inline friend Vector2 operator *(const float f, const Vector2 &v) { return Vector2(v.x * f, v.y * f); }
	inline friend Vector2 operator /(const float f, const Vector2 &v) { return Vector2(v.x / f, v.y / f); }
	bool operator < (const Vector2 &rhs) const;
	bool operator <=(const Vector2 &rhs) const;
	bool operator > (const Vector2 &rhs) const;
	bool operator >=(const Vector2 &rhs) const;
	bool isApproximately(const Vector2 &other);

	/// Returns the positive angle between this vector and the passed one in the range of [0,pi]
	inline float   angle(const Vector2& v2) const { return acos((x * v2.x + y * v2.y) / sqrt((x * x + y * y) * (v2.x * v2.x + v2.y * v2.y))); }
	/// Computes the length of the vector in the L2 norm
	inline float   length() const { return sqrt(x * x + y * y); }
	/// Computes the squared length (faster, as no square root is needed)
	inline float   lengthSquared() const { return x * x + y * y; }
	/**
	 * Assumption: The length of this vector is not approximately zero.
	 * @return: A copy of this vector with unit length.
	 */
	inline Vector2 normalized() const { return *this / sqrt(x * x + y *y); }
	/// Computes a vector that is perpendicular to this one
	inline Vector2 perpendicularVector() const { return Vector2(y, - x); }
	/// Computes the dot product between this vector and the passed one
	inline float   dot(const Vector2& v2) const { return x * v2.x + y * v2.y; }

	/// Computes a vector perpendicular to the distance vector from v2 to this vector
	inline Vector2 normal(const Vector2& v2) const { return Vector2(y - v2.y, v2.x - x).normalized(); }
	/// Interpolates linearly between this vector and the passed one
	inline Vector2 interpolateLinear(const Vector2& v2, float percent) const { return *this + (v2 - *this) * percent; }
};

/// Computes the signed angle between the two passed vectors
/// (the angle from u to v) in the range [-pi, pi].
inline float vectorAngle(const Vector2 &u, const Vector2& v) {
	Vector2 un = u.normalized();
	Vector2 vn = v.normalized();
	float r = un.dot(vn);
	if (r < -1.0f) r = -1.0f;
	if (r > 1.0f) r = 1.0f;
	return ((u.x*v.y < u.y*v.x) ? -1.0f : 1.0f) * acos(r);
}

#endif /* MATH_VECTOR2_HPP_ */
