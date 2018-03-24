/*
 * ParseIRI.cpp
 *
 *  Created on: 16.03.2018
 *      Author: christoph
 */

#include <boost/regex.hpp>
#include "ParseException.hpp"
#include "ParseIRI.hpp"

// https://www.w3.org/TR/SVG11/linking.html#IRIReference
// Please note: The following two functions only check for the pattern "url(#<ID>)" and don't validate that "<ID>" only contains valid IRI characters.

/// Format: "#<ID>"
std::string parseIRI(const std::string &iri) {
	boost::regex iriRegex("\\s*#(\\S+)\\s*");
	boost::cmatch what;
	if(boost::regex_match(iri.c_str(), what, iriRegex)) {
		return what[1];
	} else {
		throw ParseException("Invalid IRI.");
	}
}
/// Format: "url(#<ID>)"
std::string parseFuncIRI(const std::string &funcIRI) {
	boost::regex funcIRIRegex("\\s*url\\s*\\(\\s*#(\\S+)\\s*\\)\\s*");
	boost::cmatch what;
	if(boost::regex_match(funcIRI.c_str(), what, funcIRIRegex)) {
		return what[1];
	} else {
		throw ParseException("Invalid functional IRI.");
	}
}

