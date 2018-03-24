/*
 * ParseIRI.hpp
 *
 *  Created on: 16.03.2018
 *      Author: christoph
 */

#ifndef SVG_PARSE_PARSEIRI_HPP_
#define SVG_PARSE_PARSEIRI_HPP_

#include <string>

// https://www.w3.org/TR/SVG11/linking.html#IRIReference
// Please note: The following two functions only check for the pattern "url(#<ID>)" and don't validate that "<ID>" only contains valid IRI characters.

/// Format: "#<ID>"
std::string parseIRI(const std::string &iri);

/// Format: "url(#<ID>)"
std::string parseFuncIRI(const std::string &funcIRI);

#endif /* SVG_PARSE_PARSEIRI_HPP_ */
