/*
 * TestParsePath.hpp
 *
 *  Created on: 18.03.2018
 *      Author: christoph
 */

#ifndef TESTS_TESTPARSEPATH_HPP_
#define TESTS_TESTPARSEPATH_HPP_

#include <iostream>
#include <cxxtest/TestSuite.h>
#include <SVG/Parse/ParseException.hpp>
#include <SVG/Parse/Tokens.hpp>
#include <SVG/Parse/ParsePath.hpp>

using namespace std;

/**
 * Tests whether the parsing of SVG paths works correctly.
 */
class TestParseColor : public CxxTest::TestSuite
{
public:
	/*void testPathParsing() {
		vector<string> pathTokens = {"M", "1.2", "-3.4", "L", "10e-2", "-1"};
		string pathString = "M1.2 -3.4 l 10e-2 -1";
		TS_ASSERT_EQUALS(pathTokens, splitPathString(pathString));
	}

	void testNumberParsing() {
		TS_ASSERT(regexMatches("1", NUMBER_REGEX_STRING));
		TS_ASSERT(regexMatches("-9", NUMBER_REGEX_STRING));
		TS_ASSERT(regexMatches("1.0", NUMBER_REGEX_STRING));
		TS_ASSERT(regexMatches("0.1", NUMBER_REGEX_STRING));
		TS_ASSERT(regexMatches("+0.9", NUMBER_REGEX_STRING));
		TS_ASSERT(regexMatches("-0.9", NUMBER_REGEX_STRING));
		TS_ASSERT(regexMatches(".55", NUMBER_REGEX_STRING));
		TS_ASSERT(regexMatches("123.", NUMBER_REGEX_STRING));
		TS_ASSERT(regexMatches("-123.456", NUMBER_REGEX_STRING));
		TS_ASSERT(regexMatches("+10e-2", NUMBER_REGEX_STRING));
		TS_ASSERT(regexMatches("2E5", NUMBER_REGEX_STRING));

		TS_ASSERT(!regexMatches(".", NUMBER_REGEX_STRING));
		TS_ASSERT(!regexMatches("1.2.", NUMBER_REGEX_STRING));
		TS_ASSERT(!regexMatches(".1.", NUMBER_REGEX_STRING));
		TS_ASSERT(!regexMatches("1f3", NUMBER_REGEX_STRING));
		TS_ASSERT(!regexMatches("12f", NUMBER_REGEX_STRING));
		TS_ASSERT(!regexMatches("abc", NUMBER_REGEX_STRING));
		TS_ASSERT(!regexMatches("", NUMBER_REGEX_STRING));
	}*/
};

#endif /* TESTS_TESTPARSEPATH_HPP_ */
