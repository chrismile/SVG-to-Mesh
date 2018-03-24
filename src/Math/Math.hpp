/*
 * Math.hpp
 *
 *  Created on: 16.03.2018
 *      Author: christoph
 */

#ifndef MATH_MATH_HPP_
#define MATH_MATH_HPP_

/** @file
 * This file contains some maths utility functions and includes the standard C++ math header.
 */

#include <cmath>

namespace Math
{

const float PI = 3.1415926535897932f;
const float TWO_PI = PI * 2.0f;
const float HALF_PI = PI / 2.0f;
const float FLOAT_EPSILON = 0.00001f;

/**
 * Condition: max >= min.
 * Clamps 'val' to the range [min; max].
 */
template <typename T> inline T clamp(T val, T min, T max) {
	return val < min ? min : (val > max ? max : val);
}


/// Returns whether f1 is approximately equal to f2
inline bool floatEquals(float f1, float f2) {
	return std::abs(f1 - f2) <= FLOAT_EPSILON;
}

/// Converts degrees to radians
inline float degToRad(float val) { return val / 180.0f * PI; }
/// Converts radians to degrees
inline float radToDeg(float val) { return val * 180.0f / PI; }

}

#endif /* MATH_MATH_HPP_ */
