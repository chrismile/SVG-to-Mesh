/*
 * ParsePath.cpp
 *
 *  Created on: 17.03.2018
 *      Author: christoph
 */

#include "Tokens.hpp"
#include "ParsePath.hpp"

using namespace std;

std::vector<std::string> splitPathString(const std::string &pathStr) {
	//return getTokenList(pathStr, "((\\d|\\.|-|\\+|e|E)+)|[[:alnum:]]");
	return getTokenList(pathStr, string() + NUMBER_REGEX_STRING + "|[MmZzLlHhVvCcSsQqTtAa]");
}

// Splits a string like "M10.1,20.2 30,40" into "M", "10.1", "20.2", "30", "40"
/*void splitPathString(const string &path, vector<string> &splitPath) {
	string element = "";
	for (auto it = path.begin(); it != path.end(); ++it) {
		// While there's a delimiting character
		while (it != path.end() && (*it == ' ' || *it == '\t' || *it == '\n' || *it == ',')) {
			if (element.length() > 0) {
				splitPath.push_back(element);
				element = "";
			}
			++it;
		}

		if (*it == '+' || *it == '-' || *it == '.' || *it == '0'
				|| *it == '1' || *it == '2' || *it == '3'
				|| *it == '4' || *it == '5' || *it == '6'
				|| *it == '7' || *it == '8' || *it == '9'
				|| *it == 'e' || *it == 'E') {
			// One of the charactes valid for coordinate data and parameters!
			element += *it;
		} else {
			// We obviously have a command char like M, m, L, l, A, a, usw.
			if (element.length() > 0) {
				splitPath.push_back(element);
				element = "";
			}
			splitPath.push_back(string(1, *it));
		}
	}

	// If there's still a string that wasn't added, insert it at the end of the list.
	if (element.length() > 0) {
		splitPath.push_back(element);
		element = "";
	}
}
*/
