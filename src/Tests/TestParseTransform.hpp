/*
 * TestParseTransform.hpp
 *
 *  Created on: 24.03.2018
 *      Author: christoph
 */

#ifndef TESTS_TESTPARSETRANSFORM_HPP_
#define TESTS_TESTPARSETRANSFORM_HPP_

#include <iostream>
#include <cxxtest/TestSuite.h>
#include <Math/Matrix3.hpp>
#include <SVG/Parse/ParseException.hpp>
#include <SVG/Parse/ParseTransform.hpp>

/**
 * Tests whether the SVG object transform parsing functions from <SVG/Parse/ParseColor.hpp> work correctly.
 */
class TestParseTransform : public CxxTest::TestSuite
{
public:
	void testBasicsTransforms() {
		TS_ASSERT_EQUALS(Matrix3::Translation(Vector2(-10, 20)), parseElementTransformString("translate(-10, 20)"));
		TS_ASSERT_EQUALS(Matrix3::Translation(Vector2(-10, 0)), parseElementTransformString("translate(-10)"));
		TS_ASSERT_EQUALS(Matrix3::Rotation(45.0f/180.0f*PI), parseElementTransformString("rotate(45)"));
		TS_ASSERT_EQUALS(Matrix3::Translation(Vector2(2, -5))*Matrix3::Rotation(45.0f/180.0f*PI)*Matrix3::Translation(Vector2(-2, 5)),
				parseElementTransformString("rotate(45 2 -5)"));
		TS_ASSERT_EQUALS(Matrix3::Scale(2), parseElementTransformString("scale(2)"));
		TS_ASSERT_EQUALS(Matrix3::Scale(Vector2(2, 3)), parseElementTransformString("scale(2, 3)"));
	}

	void testChainedTransforms() {
		TS_ASSERT_EQUALS(Matrix3::Scale(Vector2(2, 3))*Matrix3::Translation(Vector2(-10, 20)),
				parseElementTransformString("scale(2, 3) translate(-10, 20)"));
		TS_ASSERT_EQUALS(Matrix3::Translation(Vector2(-10, 20))*Matrix3::Scale(Vector2(2, 3)),
				parseElementTransformString("translate(-10, 20) scale(2, 3)"));
	}

	void testInvalidTransforms() {
		TS_ASSERT_THROWS(parseElementTransformString("sthelse(-10, 20)"), ParseException);
		TS_ASSERT_THROWS(parseElementTransformString("translate(-10, 20"), ParseException);
		TS_ASSERT_THROWS(parseElementTransformString("matrix(-10)"), ParseException);
		TS_ASSERT_THROWS(parseElementTransformString("translate(abc)"), ParseException);
	}
};

#endif /* TESTS_TESTPARSETRANSFORM_HPP_ */
