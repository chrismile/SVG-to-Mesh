/*
 * Parse.hpp
 *
 *  Created on: 16.03.2018
 *      Author: christoph
 */

#ifndef UTILS_PARSEEXCEPTION_HPP_
#define UTILS_PARSEEXCEPTION_HPP_

#include <string>
#include <exception>
#include <boost/regex.hpp>

struct ParseException : public std::exception {
private:
	std::string description;
public:
	ParseException(const std::string &_description) {
		description = std::string() + "ParseException: " + _description;
	}

   const char *what() const throw() {
      return description.c_str();
   }
};

#endif /* UTILS_PARSEEXCEPTION_HPP_ */
