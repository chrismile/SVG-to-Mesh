/*
 * ParsePath.hpp
 *
 *  Created on: 17.03.2018
 *      Author: christoph
 */

#ifndef SVG_PARSE_PARSEPATH_HPP_
#define SVG_PARSE_PARSEPATH_HPP_

#include <string>
#include <map>

/**
 * https://www.w3.org/TR/SVG11/paths.html#PathData
 * Parses the path data of an SVG path and returns a list of tokens.
 * Please note: No validation on the data is performed.
 */
std::vector<std::string> splitPathString(const std::string &pathStr);

#endif /* SVG_PARSE_PARSEPATH_HPP_ */
