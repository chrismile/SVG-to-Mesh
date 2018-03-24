/*
 * Matrix3.hpp
 *
 *  Created on: 17.02.2016
 *      Author: Christoph Neuhauser
 */

#ifndef MATH_MATRIX3_HPP_
#define MATH_MATRIX3_HPP_

#include <cstring>
#include "Math.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

using namespace std;

/**
 * Represents a 3x3 float matrix used for projective transformations in 2D space.
 */
class Matrix3
{
public:
	union {
		struct {
			float m11, m12, m13,
				  m21, m22, m23,
				  m31, m32, m33;
		};

		float m[3][3]; ///< Two-dimensional array
		float n[9];   ///< One-dimensional array
	};

	Matrix3() {}

	Matrix3(const Matrix3 &m)
	: m11(m.m11), m12(m.m12), m13(m.m13),
	  m21(m.m21), m22(m.m22), m23(m.m23),
	  m31(m.m31), m32(m.m32), m33(m.m33) {}

	Matrix3(float _m11, float _m12, float _m13,
	        float _m21, float _m22, float _m23,
	        float _m31, float _m32, float _m33)
	: m11(_m11), m12(_m12), m13(_m13),
	  m21(_m21), m22(_m22), m23(_m23),
	  m31(_m31), m32(_m32), m33(_m33) {}

	inline const float* operator[] (size_t row) const { return m[row]; }
	inline float* operator[] (size_t row) { return m[row]; }

	/// Returns the 3x3 identity matrix.
	static Matrix3 Identity() {
		return Matrix3(1, 0, 0,
		               0, 1, 0,
					   0, 0, 1);
	}

	/// Returns a matrix consisting only of zeroes.
	static Matrix3 Null() {
		return Matrix3(0, 0, 0,
		               0, 0, 0,
					   0, 0, 0);
	}

	/// Returns a matrix representing a translation by the vector 't'.
	static Matrix3 Translation(const Vector2 &t) {
		return Matrix3(1, 0, t.x,
		               0, 1, t.y,
					   0, 0, 1);
	}

	/**
	 * Returns a matrix representing a counterclockwise rotation around the origin by an angle 'r'.
	 * @arg r: The angle in radians
	 */
	static Matrix3 Rotation(float r) {
		float c = cos(r);
		float s = sin(r);
		return Matrix3(c, -s, 0,
		               s,  c, 0,
					   0,  0, 1);
	}

	/**
	 * Returns a matrix representing a scaling operation around the origin.
	 * @arg s: The scale in x and y direction
	 */
	static Matrix3 Scale(const Vector2 &s) {
		return Matrix3(s.x, 0, 0,
		               0, s.y, 0,
					   0, 0,   1);
	}
	/// Returns a matrix representing a scaling operation around the origin.
	static Matrix3 Scale(float s) {
		return Matrix3(s, 0, 0,
		               0, s, 0,
					   0, 0, 1);
	}

	const Matrix3 &operator=(const Matrix3 &rhs) {
		memcpy(this->n, rhs.n, 9*sizeof(float));
		return *this;
	}

	/// Matrix-matrix multiplication
	Matrix3 operator*(const Matrix3 &rhs) const {
		Matrix3 m;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m.m[i][j] = this->m[i][0]*rhs.m[0][j] + this->m[i][1]*rhs.m[1][j] + this->m[i][2]*rhs.m[2][j];
			}
		}
		return m;
	}

	/// Matrix-matrix multiplication
	void operator*=(const Matrix3 &rhs) {
		Matrix3 m;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m.m[i][j] = this->m[i][0]*rhs.m[0][j] + this->m[i][1]*rhs.m[1][j] + this->m[i][2]*rhs.m[2][j];
			}
		}
		*this = m;
	}

	/// Matrix-vector multiplication (assumes homogenous coordinate 1)
	Vector2 operator*(const Vector2 &rhs) const {
		float x = m11*rhs.x + m12*rhs.y + m13;
		float y = m21*rhs.x + m22*rhs.y + m23;
		float z = m31*rhs.x + m32*rhs.y + m33;
		return Vector2(x/z, y/z);
	}

	/// Matrix-vector multiplication
	Vector3 operator*(const Vector3 &rhs) const {
		Vector3 v;
		v.x = m11*rhs.x + m12*rhs.y + m13 * rhs.z;
		v.y = m21*rhs.x + m22*rhs.y + m23 * rhs.z;
		v.z = m31*rhs.x + m32*rhs.y + m33 * rhs.z;
		return v;
	}

	/// Computes the determinant of this matrix
	float determinant() {
		return m11 * (m22*m33 - m23*m32) + m12 * (m21*m33 - m23*m31) + m13 * (m21*m32 - m22*m31);
	}

	/**
	 * Condition: determinant() != 0
	 * Computes the inverse matrix of this matrix
	 */
	Matrix3 inverse() {
		// Compute the determinant of the matrix and cache computed values also used later
		float detVal1 = m22 * m33 - m23 * m32;
		float detVal2 = m23 * m31 - m21 * m33;
		float detVal3 = m21 * m32 - m22 * m31;
		float invDet = 1.0f / (m11 * detVal1 + m12 * detVal2 + m13 * detVal3);

		// Now compute the inverse matrix using the inverse determinant
		Matrix3 invMat;
		invMat.m11 = detVal1 * invDet;
		invMat.m12 = (m13 * m32 - m12 * m33) * invDet;
		invMat.m13 = (m12 * m23 - m13 * m22) * invDet;
		invMat.m21 = detVal2 * invDet;
		invMat.m22 = (m11 * m33 - m13 * m31) * invDet;
		invMat.m23 = (m21 * m13 - m11 * m23) * invDet;
		invMat.m31 = detVal3 * invDet;
		invMat.m32 = (m31 * m12 - m11 * m32) * invDet;
		invMat.m33 = (m11 * m22 - m21 * m12) * invDet;

		return invMat;
	}

	/**
	 * Condition: The transformation this matrix represents consists only of the concatenation
	 *  	of translations, scalings and rotations.
	 * Decomposes this matrix into translation, scale and rotation.
	 * @param[out] translation: The translational part (reference)
	 * @param[out] scale: The translational part (reference)
	 * @param[out] rotation: The translational part(reference)
	 */
	void decompose(Vector2 &translation, Vector2 &scale, float &rotation) const
	{
		translation.x = m13;
		translation.y = m23;
		scale.x = sqrt((m11 * m11) + (m21 * m21));
		scale.y = sqrt((m12 * m12) + (m22 * m22));

		rotation = -atan2(m12, m22);
		//rotation = -Math::atan2(-m21, m11); // alternative #2
		if (rotation < 0) {
			rotation += Math::TWO_PI;
		}

		// scale(-1, -1) == rotation(180deg). Thus, we only need to detect single axis mirroring.
		// If the cross product of the matrix's x and y axis is negative, the object needs to be mirrored.
		// The code commented out is the unoptimized version of the algorithm.
		/*Vector2 right(1,0), top(0,1);
		right = Vector2(m11*right.x + m12*right.y, m21*right.x + m22*right.y);
		top = Vector2(m11*top.x + m12*top.y, m21*top.x + m22*top.y);
		if (right.cross(top) < 0) {
			scale.x *= -1; // scale.y if alternative #2
		}*/
		/*if (Vector2(m11, m21).cross(Vector2(m12, m22)) < 0) {
			scale.x *= -1; // scale.y if alternative #2
		}*/
		if (m11 * m22 - m21 * m12 < 0) {
			scale.x *= -1; // scale.y if alternative #2
		}

		/*cout << "tx: " << translation.x << ", ty: " << translation.y
				<< ", sx: " << scale.x << ", sy: " << scale.y << ", r: " << rotation
				<< ", sgn: " << Math::sign(m11) << "|" << Math::sign(m21) << "|"
				             << Math::sign(m12) << "|" << Math::sign(m22) << endl;*/
	}

	/// Returns whether this matrix is an identity matrix.
	bool isIdentity() {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (!Math::floatEquals(m[i][j], i == j ? 1.0f : 0.0f))
					return false;
			}
		}
		return true;
	}
};

#endif /* MATH_MATRIX3_HPP_ */
