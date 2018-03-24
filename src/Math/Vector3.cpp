/*
 * Vector3.cpp
 *
 *  Created on: 18.02.2016
 *      Author: Christoph Neuhauser
 */

#include "Vector3.hpp"
#include <Math/Math.hpp>

bool Vector3::operator ==(const Vector3 &rhs) const
{
	if(x == rhs.x && y == rhs.y && z == rhs.z) {
		return true;
	} else {
		return false;
	}
}

void Vector3::operator =(const Vector3 &rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
}

void Vector3::operator +=(const Vector3 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

void Vector3::operator -=(const Vector3 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
}

void Vector3::operator *=(const Vector3 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
}

void Vector3::operator /=(const Vector3 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;
}

Vector3 Vector3::operator +(const Vector3 &rhs) const
{
	Vector3 temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	temp.z = z + rhs.z;
	return temp;
}

Vector3 Vector3::operator -(const Vector3 &rhs) const
{
	Vector3 temp;
	temp.x = x - rhs.x;
	temp.y = y - rhs.y;
	temp.z = z - rhs.z;
	return temp;
}

Vector3 Vector3::operator *(const Vector3 &rhs) const
{
	Vector3 temp;
	temp.x = x * rhs.x;
	temp.y = y * rhs.y;
	temp.z = z * rhs.z;
	return temp;
}

Vector3 Vector3::operator /(const Vector3 &rhs) const
{
	Vector3 temp;
	temp.x = x / rhs.x;
	temp.y = y / rhs.y;
	temp.z = z / rhs.z;
	return temp;
}

bool Vector3::operator <(const Vector3 &rhs) const
{
	if (x < rhs.x) {
		return true;
	}
	return false;
}

bool Vector3::operator <=(const Vector3 &rhs) const
{
	if (x <= rhs.x) {
		return true;
	}
	return false;
}


bool Vector3::operator >(const Vector3 &rhs) const
{
	if (x > rhs.x) {
		return true;
	}
	return false;
}


bool Vector3::operator >=(const Vector3 &rhs) const
{
	if (x >= rhs.x) {
		return true;
	}
	return false;
}


bool Vector3::isApproximately(const Vector3 &other)
{
	return Math::floatEquals(x, other.x) && Math::floatEquals(y, other.y) && Math::floatEquals(z, other.z);
}
