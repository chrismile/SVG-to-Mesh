/*
 * AABB2.hpp
 *
 *  Created on: 10.01.2015
 *      Author: Christoph Neuhauser
 */

#ifndef MATH_AABB2_HPP_
#define MATH_AABB2_HPP_

#include "Vector2.hpp"
#include <cfloat>

class Matrix3;

/**
 * Represents an 2D axis aligned bounding box specified by its lower left and upper right corner.
 */
class AABB2
{
public:
	AABB2() : minimum(FLT_MAX, FLT_MAX), maximum(-FLT_MAX, -FLT_MAX) {}
	AABB2(const Vector2 &_minimum, const Vector2 &_maximum) : minimum(_minimum), maximum(_maximum) {}

	inline void setMinimum(const Vector2 &_minimum) { minimum = _minimum; }
	inline void setMaximum(const Vector2 &_maximum) { maximum = _maximum; }
	inline void setX(float x) { minimum.x = x; }
	inline void setY(float y) { minimum.y = y; }
	inline void setPos(const Vector2 &_minimum) { minimum = _minimum; }
	inline void setW(float w) { maximum.x = minimum.x + w; }
	inline void setH(float h) { maximum.y = minimum.y + h; }
	inline void setDimensions(const Vector2 &dimensions) { maximum = Vector2(minimum.x + dimensions.x, minimum.y + dimensions.y); }

	inline const Vector2 &getMinimum() const { return minimum; }
	inline const Vector2 &getMaximum() const { return maximum; }
	inline Vector2 &getMinimum() { return minimum; }
	inline Vector2 &getMaximum() { return maximum; }
	inline float getX() const { return minimum.x; }
	inline float getY() const { return minimum.y; }
	inline const Vector2 &getPos() const { return minimum; }
	inline float getW() const { return maximum.x - minimum.x; }
	inline float getH() const { return maximum.y - minimum.y; }
	inline Vector2 getDimensions() const { return Vector2(maximum.x - minimum.x, maximum.y - minimum.y); }
	inline Vector2 getExtent() const { return getDimensions()/2.0f; }
	inline Vector2 getCenter() const { return Vector2((maximum.x + minimum.x) / 2.0f, (maximum.y + minimum.y) / 2.0f); }
	inline float getArea() const { return (maximum.x - minimum.x)*(maximum.y - minimum.y); }

	/// Merge this bounding box with the passed one
	void combine(const AABB2 &otherAABB);
	/// Update this bounding box to contain the passed point
	void addPoint(const Vector2 &point);

	/// Transform the AABB with the passed transformation matrix and return the result
	AABB2 transformed(const Matrix3 &matrix);
	/// Scale the extents of this bounding box and return the result (original bounding box not changed)
	AABB2 getScaledAABB(float scaleFactor);

	/// Returns whether this AABB and the passed one intersect
	bool intersects(const AABB2 &otherAABB) const;
	/// Returns whether this AABB contains the passed one
	bool contains(const AABB2 &otherAABB) const;
	/// Returns whether this AABB contains the passed point
	bool contains(const Vector2 &point) const;

private:
	Vector2 minimum, maximum; ///< Lower left and upper right corner
};

#endif /* MATH_AABB2_HPP_ */
