/*
 * Tokens.cpp
 *
 *  Created on: 18.03.2018
 *      Author: christoph
 */

#include "Tokens.hpp"
#include <boost/regex.hpp>

std::vector<std::string> getTokenList(const std::string &str, const std::string &exprStr) {
	std::vector<std::string> tokenList;
	boost::regex expr(exprStr.c_str());
	boost::regex_token_iterator<std::string::const_iterator> it{str.begin(), str.end(), expr};
	boost::regex_token_iterator<std::string::const_iterator> end;
	while (it != end) {
		std::string token = *it++;
		tokenList.push_back(token);
	}
	return tokenList;
}

bool regexMatches(const std::string &str, const std::string &exprStr) {
	boost::regex regexp(exprStr);
	boost::cmatch what;
	return boost::regex_match(str.c_str(), what, regexp);
}
