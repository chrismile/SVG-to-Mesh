/*
 * ParseTransform.cpp
 *
 *  Created on: 17.03.2018
 *      Author: christoph
 */

#include <boost/regex.hpp>
#include <Utils/Convert.hpp>
#include "Tokens.hpp"
#include "ParseTransform.hpp"

using namespace std;

Matrix3 parseElementTransformMatrix(XMLElement *svgElement)
{
	Matrix3 matrix = Matrix3::Identity();
	if (!svgElement->Attribute("transform")) {
		return matrix;
	}

	// Get the transform attribute of the XML element
	string transformString = svgElement->Attribute("transform");

	// Iterate over all of the concatenated transformations (pattern: "type(content)").
	// First match: Transform type. Second match: Transform information in the brackets.
	boost::regex transformRegex("(\\S+)\\s*\\(\\s*(\\S+)\\s*\\)(.*)");
	boost::smatch what;
	while (regex_search(transformString, what, transformRegex)) {
		string transformType = what[1];
		string transformContent = what[2];
		transformString = what[3]; // Continue with next part of string

		// Now split the transform content in the brackets (multiple float values separated by space or commas).
		vector<string> transformData = getTokenList(transformContent, NUMBER_REGEX_STRING/*"(\\w|\\.|-|\\+|e|E)+"*/);

		if (transformType == "translate") {
			float x = Convert::fromString<float>(transformData.at(0));
			float y = Convert::fromString<float>(transformData.at(1));
			matrix = matrix * Matrix3::Translation(Vector2(x, -y));
		} else if (transformType == "scale") {
			float scaleX = Convert::fromString<float>(transformData.at(0));
			if (transformData.size() == 1) {
				matrix = matrix * Matrix3::Scale(Vector2(scaleX, scaleX));
			} else {
				float scaleY = Convert::fromString<float>(transformData.at(1));
				matrix = matrix * Matrix3::Scale(Vector2(scaleX, scaleY));
			}
		} else if (transformType == "rotate") {
			float rot = Convert::fromString<float>(transformData.at(0));
			if (transformData.size() == 3) {
				// Use a certain center of rotation
				float x = Convert::fromString<float>(transformData.at(1));
				float y = Convert::fromString<float>(transformData.at(2));
				matrix = matrix * Matrix3::Translation(Vector2(-x, y))
						* Matrix3::Rotation(rot) * Matrix3::Translation(Vector2(x, -y));
			} else {
				matrix = matrix * Matrix3::Rotation(rot);
			}
		} else if (transformType == "matrix") {
			float m0 = Convert::fromString<float>(transformData.at(0));
			float m1 = Convert::fromString<float>(transformData.at(1));
			float m2 = Convert::fromString<float>(transformData.at(2));
			float m3 = Convert::fromString<float>(transformData.at(3));
			float m4 = Convert::fromString<float>(transformData.at(4));
			float m5 = Convert::fromString<float>(transformData.at(5));

			matrix = matrix * Matrix3(
					m0,   m2,    m4,
					m1,   m3,   -m5, // -m5 because of inverted y axis
					0.0f, 0.0f, 1.0f);
		}
	}

	return matrix;
}
