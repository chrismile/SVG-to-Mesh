/*
 * TestParseColor.hpp
 *
 *  Created on: 17.03.2018
 *      Author: christoph
 */

#ifndef _TESTPARSECOLOR_HPP_
#define _TESTPARSECOLOR_HPP_

#include <iostream>
#include <cxxtest/TestSuite.h>
#include <SVG/Parse/ParseException.hpp>
#include <SVG/Parse/ParseColor.hpp>

/**
 * Tests whether the CSS3 color parsing functions from <SVG/Parse/ParseColor.hpp> work correctly.
 */
class TestParseColor : public CxxTest::TestSuite
{
public:
	void testHexColor() {
		TS_ASSERT_EQUALS(Color(1, 2, 3), parseCSS3ColorString("#010203"));
		TS_ASSERT_EQUALS(Color(1, 2, 3), parseCSS3ColorString(" #010203 "));
		TS_ASSERT_EQUALS(Color(0xa1, 0xb5, 0x6e), parseCSS3ColorString("#a1b56e"));
	}

	void testRGBColor() {
		TS_ASSERT_EQUALS(Color(1, 2, 3), parseCSS3ColorString("rgb(1, 2, 3)"));
		TS_ASSERT_EQUALS(Color(1, 2, 3), parseCSS3ColorString(" rgb ( 1 , 2 , 3 ) "));
	}

	void testRGBPercentColor() {
		TS_ASSERT_EQUALS(Color(25, 51, 127), parseCSS3ColorString("rgb(10%, 20%, 50%)"));
	}

	void testInvalidColors() {
		TS_ASSERT_THROWS(parseCSS3ColorString("#1"), ParseException);
		TS_ASSERT_THROWS(parseCSS3ColorString("#12"), ParseException);
		TS_ASSERT_THROWS(parseCSS3ColorString("#"), ParseException);
		TS_ASSERT_THROWS(parseCSS3ColorString(""), ParseException);

		TS_ASSERT_THROWS(parseCSS3ColorString("rgb(1)"), ParseException);
		TS_ASSERT_THROWS(parseCSS3ColorString("rgb(1, 2)"), ParseException);
		TS_ASSERT_THROWS(parseCSS3ColorString("rgb()"), ParseException);
		TS_ASSERT_THROWS(parseCSS3ColorString("rgb("), ParseException);
		TS_ASSERT_THROWS(parseCSS3ColorString("rgb)"), ParseException);
		TS_ASSERT_THROWS(parseCSS3ColorString("rgb"), ParseException);
		TS_ASSERT_THROWS(parseCSS3ColorString("rgb(a, b, c)"), ParseException);
	}
};

#endif
