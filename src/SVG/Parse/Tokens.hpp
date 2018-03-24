/*
 * Tokens.hpp
 *
 *  Created on: 18.03.2018
 *      Author: christoph
 */

#ifndef SVG_PARSE_TOKENS_HPP_
#define SVG_PARSE_TOKENS_HPP_

#include <string>
#include <vector>

/**
 * Regex string for token parsing of SVG numbers.
 * First part: Integer number (e.g. -10)
 * Second part: Floating point (e.g. 12.34 or -.12)
 * Third part: Exponential notation (e.g. 10e-2).
 */
const std::string NUMBER_REGEX_STRING = "([\\+-]?(([[:digit:]]+)|(([[:digit:]]*)?\\.([[:digit:]]+)?)|([[:digit:]]+[eE][\\+-]?[[:digit:]]+)))";

/**
 * Returns a list containing all tokens in 'str' specified by 'exprStr'.
 * @param str: The string to parse.
 * @param exprStr: A regular expression string describing the structure of a token.
 */
std::vector<std::string> getTokenList(const std::string &str, const std::string &exprStr);

/**
 * Tests whether the string 'str' marches the regex string 'exprStr'.
 * @param str: The string to test.
 * @param exprStr: The regular expression.
 */
bool regexMatches(const std::string &str, const std::string &exprStr);

#endif /* SVG_PARSE_TOKENS_HPP_ */
