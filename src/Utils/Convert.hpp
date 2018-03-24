/*
 * Convert.hpp
 *
 *  Created on: 14.03.2018
 *      Author: christoph
 */

#ifndef UTILS_CONVERT_HPP_
#define UTILS_CONVERT_HPP_

#include <string>
#include <vector>
#include <string>
#include <sstream>

namespace Convert
{

/// Conversion of an arbitrary type to a string
template <class T>
std::string toString(T obj)
{
	std::ostringstream ostr;
	ostr << obj;
	return ostr.str();
}

/// Converts a string to an arbitrary number type
template <class T>
T fromString (const std::string &stringObject)
{
	std::stringstream strstr;
	strstr << stringObject;
	T type;
	strstr >> type;
	return type;
}
inline std::string fromString (const std::string &stringObject) {
	return stringObject;
}

/// Converts hexadecimal number string to an arbitrary integer number type
template <class T>
T numFromHexString(const std::string &stringObject) {
	std::stringstream strstr;
	strstr << std::hex << stringObject;
	T type;
	strstr >> type;
	return type;
}

/// Converts arbitrary integer number type to a hexadecimal number string
template <class T>
std::string numToHexString(T obj) {
	std::ostringstream ostr;
	ostr << std::hex << obj;
	return ostr.str();
}

/**
 * Appends @arg vector2 to @arg vector1.
 */
template<class T>
void appendVector(std::vector<T> &vector1, std::vector<T> &vector2)
{
	vector1.insert(vector1.end(), vector2.begin(), vector2.end());
}

}

#endif /* UTILS_CONVERT_HPP_ */
