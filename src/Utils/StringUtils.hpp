/*
 * StringUtils.hpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#ifndef UTILS_STRINGUTILS_HPP_
#define UTILS_STRINGUTILS_HPP_

#include <string>

using namespace std;

int isWhitespace(int c) {
	return c == ' ' || c == '\t';
}

inline void removeWhitespace(std::string &str) {
	str.erase(remove_if(str.begin(), str.end(), isWhitespace), str.end());
}

/// Only remove whitespace at start and end of the string
inline void trimString(std::string &str) {
	str.erase(remove_if(str.begin(), str.end(), isWhitespace), str.end());
}

#endif /* UTILS_STRINGUTILS_HPP_ */
