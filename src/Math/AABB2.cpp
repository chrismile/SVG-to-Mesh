/*
 * AABB2.cpp
 *
 *  Created on: 07.02.2015
 *      Author: Christoph Neuhauser
 */

#include "AABB2.hpp"
#include "Vector2.hpp"
#include "Matrix3.hpp"
#include <Math/Math.hpp>

void AABB2::combine(const AABB2 &otherAABB)
{
	if (otherAABB.minimum.x < minimum.x)
		minimum.x = otherAABB.minimum.x;
	if (otherAABB.minimum.y < minimum.y)
		minimum.y = otherAABB.minimum.y;
	if (otherAABB.maximum.x > maximum.x)
		maximum.x = otherAABB.maximum.x;
	if (otherAABB.maximum.y > maximum.y)
		maximum.y = otherAABB.maximum.y;
}

void AABB2::addPoint(const Vector2 &point)
{
	if (point.x < minimum.x)
		minimum.x = point.x;
	if (point.y < minimum.y)
		minimum.y = point.y;
	if (point.x > maximum.x)
		maximum.x = point.x;
	if (point.y > maximum.y)
		maximum.y = point.y;
}

AABB2 AABB2::transformed(const Matrix3 &matrix)
{
	Vector2 transformedCorners[4];
	transformedCorners[0] = matrix * minimum;
	transformedCorners[1] = matrix * maximum;
	transformedCorners[2] = matrix * Vector2(maximum.x, minimum.y);
	transformedCorners[3] = matrix * Vector2(minimum.x, maximum.y);

	AABB2 aabbTransformed;
	for (int i = 0; i < 4; ++i) {
		if (transformedCorners[i].x < aabbTransformed.minimum.x)
			aabbTransformed.minimum.x = transformedCorners[i].x;
		if (transformedCorners[i].x > aabbTransformed.maximum.x)
			aabbTransformed.maximum.x = transformedCorners[i].x;

		if (transformedCorners[i].y < aabbTransformed.minimum.y)
			aabbTransformed.minimum.y = transformedCorners[i].y;
		if (transformedCorners[i].y > aabbTransformed.maximum.y)
			aabbTransformed.maximum.y = transformedCorners[i].y;
	}

	return aabbTransformed;
}

AABB2 AABB2::getScaledAABB(float scaleFactor)
{
	Vector2 center = getCenter();
	Vector2 extent = getExtent() * scaleFactor;
	AABB2 scaledAABB;
	scaledAABB.setMinimum(center - extent);
	scaledAABB.setMaximum(center + extent);
	return scaledAABB;
}


bool AABB2::intersects(const AABB2 &otherAABB) const
{
	if ( (minimum.y < otherAABB.maximum.y) &&
		 (maximum.y > otherAABB.minimum.y) &&
		 (minimum.x < otherAABB.maximum.x) &&
		 (maximum.x > otherAABB.minimum.x) )
	{
		return true;
	}
	return false;
}

bool AABB2::contains(const AABB2 &otherAABB) const
{
	if ( (otherAABB.minimum.y >= minimum.y) &&
		 (otherAABB.maximum.y <= maximum.y) &&
		 (otherAABB.minimum.x >= minimum.x) &&
		 (otherAABB.maximum.x <= maximum.x) )
	{
		return true;
	}
	return false;
}

bool AABB2::contains(const Vector2 &point) const
{
	if ( (point.y >= minimum.y) &&
		 (point.y <= maximum.y) &&
		 (point.x >= minimum.x) &&
		 (point.x <= maximum.x) )
	{
		return true;
	}
	return false;
}
