/*
 * Vector2.cpp
 *
 *  Created on: 16.01.2015
 *      Author: Christoph Neuhauser
 */

#include "Vector2.hpp"
#include <Math/Math.hpp>

bool Vector2::operator ==(const Vector2 &rhs) const
{
	if(x == rhs.x && y == rhs.y) {
		return true;
	} else {
		return false;
	}
}

void Vector2::operator =(const Vector2 &rhs)
{
	x = rhs.x;
	y = rhs.y;
}

void Vector2::operator +=(const Vector2 &rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vector2::operator -=(const Vector2 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vector2::operator *=(const Vector2 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;
}

void Vector2::operator /=(const Vector2 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;
}

Vector2 Vector2::operator +(const Vector2 &rhs) const
{
	Vector2 temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	return temp;
}

Vector2 Vector2::operator -(const Vector2 &rhs) const
{
	Vector2 temp;
	temp.x = x - rhs.x;
	temp.y = y - rhs.y;
	return temp;
}

Vector2 Vector2::operator *(const Vector2 &rhs) const
{
	Vector2 temp;
	temp.x = x * rhs.x;
	temp.y = y * rhs.y;
	return temp;
}

Vector2 Vector2::operator /(const Vector2 &rhs) const
{
	Vector2 temp;
	temp.x = x / rhs.x;
	temp.y = y / rhs.y;
	return temp;
}

bool Vector2::operator <(const Vector2 &rhs) const
{
	if (x < rhs.x) {
		return true;
	}
	return false;
}

bool Vector2::operator <=(const Vector2 &rhs) const
{
	if (x <= rhs.x) {
		return true;
	}
	return false;
}


bool Vector2::operator >(const Vector2 &rhs) const
{
	if (x > rhs.x) {
		return true;
	}
	return false;
}


bool Vector2::operator >=(const Vector2 &rhs) const
{
	if (x >= rhs.x) {
		return true;
	}
	return false;
}


bool Vector2::isApproximately(const Vector2 &other)
{
	return Math::floatEquals(x, other.x) && Math::floatEquals(y, other.y);
}
