/*
 * TestParseIRI.hpp
 *
 *  Created on: 17.03.2018
 *      Author: christoph
 */
#ifndef _TESTPARSEIRI_HPP_
#define _TESTPARSEIRI_HPP_

#include <iostream>
#include <cxxtest/TestSuite.h>
#include <SVG/Parse/ParseException.hpp>
#include <SVG/Parse/ParseIRI.hpp>

/**
 * Tests whether the IRI parsing functions from <SVG/Parse/ParseIRI.hpp> work correctly
 */
class TestParseIRI : public CxxTest::TestSuite
{
public:
	void testFunIRI() {
		TS_ASSERT_EQUALS("myid", parseFuncIRI("url(#myid)"));
		TS_ASSERT_EQUALS("myid", parseFuncIRI(" url ( #myid ) "));
		TS_ASSERT_THROWS(parseFuncIRI("url(#)"), ParseException);
		TS_ASSERT_THROWS(parseFuncIRI("url(#myid somethingelse)"), ParseException);
		TS_ASSERT_THROWS(parseFuncIRI("url(#myid) somethingelse"), ParseException);
		TS_ASSERT_THROWS(parseFuncIRI("url(myid)"), ParseException);
		TS_ASSERT_THROWS(parseFuncIRI("(myid)"), ParseException);
		TS_ASSERT_THROWS(parseFuncIRI("#myid"), ParseException);
		TS_ASSERT_THROWS(parseFuncIRI("myid"), ParseException);
		TS_ASSERT_THROWS(parseFuncIRI(""), ParseException);
	}

	void testIRI() {
		TS_ASSERT_EQUALS("myid", parseIRI("#myid"));
		TS_ASSERT_EQUALS("myid", parseIRI(" #myid "));
		TS_ASSERT_THROWS(parseIRI("url(#myid)"), ParseException);
		TS_ASSERT_THROWS(parseIRI("# myid"), ParseException);
		TS_ASSERT_THROWS(parseIRI("#"), ParseException);
		TS_ASSERT_THROWS(parseIRI("myid"), ParseException);
		TS_ASSERT_THROWS(parseIRI(""), ParseException);
	}
};

#endif
