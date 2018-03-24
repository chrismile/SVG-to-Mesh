/*
 * SvgDocument.cpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#include <iostream>
#include <Utils/Convert.hpp>
#include <Math/Rectangle.hpp>
#include <SVG/Parse/Tokens.hpp>
#include "SvgDocument.hpp"

using namespace std;

SvgDocument::SvgDocument(const string &filename, const string &output) {
	// Load the SVG XML document
	if (document.LoadFile(filename.c_str()) != XML_SUCCESS) {
		cerr << "SvgFile::SvgFile: Couldn't open file \"" << filename << "\"!";
		return;
	}

	// Query the top-level node
	svgNode = document.FirstChildElement("svg");
	if (svgNode == NULL) {
		cerr << "SvgFile::SvgFile: No \"svg\" node found!" << endl;
		return;
	}

	// Get the document view box if it is set
	if (masterNode->Attribute("viewBox")) {
		vector<string> parts;
		StringMethods::get()->split(masterNode->Attribute("viewBox"), " \t,", parts);
		int x = Convert::fromString<float>(parts.at(0));
		int y = Convert::fromString<float>(parts.at(1));
		int w = Convert::fromString<float>(parts.at(2));
		int h = Convert::fromString<float>(parts.at(3));
		viewBox.setMinimum(Vector2(x, y));
		viewBox.setMaximum(Vector2(x+w, y+h));
	}

	for (XMLIterator it(svgNode); it.isValid(); ++it) {
		convertShapesToPaths(*it);
	}

	root = SvgElementPtr(new SvgGroup);
	root->parseDocument(this, svgNode);
}


void SvgDocument::convertShapesToPaths(XMLElement *parent) {
	for (XMLIterator it(parent); it.isValid(); ++it) {
		XMLElement* pathElement = *it;
		if (strcmp(pathElement->Name(), "g") == 0) {
			convertShapesToPaths(pathElement);
		} else if (strcmp(pathElement->Name(), "rect") == 0) {
			convertRectangleToPath(pathElement);
		} else if (strcmp(pathElement->Name(), "ellipse") == 0) {
			convertEllipseToPath(pathElement);
		} else if (strcmp(pathElement->Name(), "circle") == 0) {
			convertCircleToPath(pathElement);
		}
#ifdef FONT_SUPPORT
		else if (strcmp(pathElement->Name(), "text") == 0) {
			textToPath(pathElement);
		} else if (strcmp(pathElement->Name(), "flowRoot") == 0) {
			flowRootToPath(pathElement);
		}
#endif
	}
}

/// https://www.w3.org/TR/SVG11/shapes.html#RectElement
void SvgDocument::convertRectangleToPath(XMLElement *element) {
	// Create a rectangle with the appropriate data
	float x = element->FloatAttribute("x");
	float y = element->FloatAttribute("y");
	float width = element->FloatAttribute("width");
	float height = element->FloatAttribute("height");

	string rectanglePathData;

	// Rounded corners
	if (element->Attribute("rx") != NULL) {
		float rx, ry;
		rx = ry = element->FloatAttribute("rx");
		if (element->Attribute("ry") != NULL) {
			ry = element->FloatAttribute("ry");
		}
		if (rx > width / 2.0f) {
			rx = width / 2.0f;
		}
		if (ry > height / 2.0f) {
			ry = height / 2.0f;
		}

		// Set the data of the rectangle path
		rectanglePathData = string()
				+ "M " + Convert::toString(x+rx) + "," + Convert::toString(y) + " "
				+ "L " + Convert::toString(x+width-rx) + "," + Convert::toString(y) + " "
				+ "A " + Convert::toString(x+width) + "," + Convert::toString(y+ry) + " 0 0 1 "
				+ "L " + Convert::toString(x+width) + "," + Convert::toString(y+height-ry) + " "
				+ "A " + Convert::toString(x+width-rx) + "," + Convert::toString(y+height) + " 0 0 1 "
				+ "L " + Convert::toString(x+rx) + "," + Convert::toString(y+height) + " "
				+ "A " + Convert::toString(x) + "," + Convert::toString(y+height-ry) + " 0 0 1 "
				+ "L " + Convert::toString(x) + "," + Convert::toString(y+ry) + " "
				+ "A " + Convert::toString(x+rx) + "," + Convert::toString(y) + " 0 0 1 "
				+ "M " + Convert::toString(x+rx) + "," + Convert::toString(y);
	} else {
		// Set the data of the rectangle path with hard corners
		rectanglePathData = string() + "m "
				+ Convert::toString(x) + "," + Convert::toString(y) + " "
				+ Convert::toString(width) + ",0 "
				+ "0," + Convert::toString(height) + " "
				+ Convert::toString(-width) + ",0 z";
	}

	// Delete old data, set path data
	element->SetName("path");
	element->DeleteAttribute("x");
	element->DeleteAttribute("y");
	element->DeleteAttribute("width");
	element->DeleteAttribute("height");
	element->SetAttribute("d", rectanglePathData.c_str());
}

/// https://www.w3.org/TR/SVG11/shapes.html#EllipseElement
void SvgDocument::convertEllipseToPath(XMLElement *element) {
	float cx = element->FloatAttribute("cx");
	float cy = element->FloatAttribute("cy");
	float rx = element->FloatAttribute("rx");
	float ry = element->FloatAttribute("ry");

	// Delete old data
	element->SetName("path");
	element->DeleteAttribute("cx");
	element->DeleteAttribute("cy");
	element->DeleteAttribute("rx");
	element->DeleteAttribute("ry");

	// Set the data of the ellipse path
	string ellipsePathData = string()
			+ "M " + Convert::toString(cx) + "," + Convert::toString(cy)
		    + " m " + Convert::toString(-rx) + ",0"
		    + " a " + Convert::toString(rx) + "," + Convert::toString(ry) + " 0 1 0 " + Convert::toString(rx * 2) + ",0"
		    + " a " + Convert::toString(rx) + "," + Convert::toString(ry) + " 0 1 0 " + Convert::toString(-rx * 2) + ",0";
	element->SetAttribute("d", ellipsePathData.c_str());
}

/// https://www.w3.org/TR/SVG11/shapes.html#CircleElement
void SvgDocument::convertCircleToPath(XMLElement *element) {
	float cx = element->FloatAttribute("cx");
	float cy = element->FloatAttribute("cy");
	float r = element->FloatAttribute("r");

	// Delete old data
	element->SetName("path");
	element->DeleteAttribute("cx");
	element->DeleteAttribute("cy");
	element->DeleteAttribute("r");

	// Set the data of the circle path
	string circlePathData = string()
			+ "M " + Convert::toString(cx) + "," + Convert::toString(cy)
		    + " m " + Convert::toString(-r) + ",0"
		    + " a " + Convert::toString(r) + "," + Convert::toString(r) + " 0 1 0 " + Convert::toString(r * 2) + ",0"
		    + " a " + Convert::toString(r) + "," + Convert::toString(r) + " 0 1 0 " + Convert::toString(-r * 2) + ",0";
	element->SetAttribute("d", circlePathData.c_str());
}

/// https://www.w3.org/TR/SVG11/shapes.html#LineElement
void SvgDocument::convertLineToPath(XMLElement *element) {
	float x1 = element->FloatAttribute("x1");
	float y1 = element->FloatAttribute("y1");
	float x2 = element->FloatAttribute("x2");
	float y2 = element->FloatAttribute("y2");

	// Delete old data
	element->SetName("path");
	element->DeleteAttribute("x1");
	element->DeleteAttribute("y1");
	element->DeleteAttribute("x2");
	element->DeleteAttribute("y2");

	// Set the data of the line path
	string linePathData = string()
			+ "M " + Convert::toString(x1) + "," + Convert::toString(y1)
		    + " L " + Convert::toString(x2) + "," + Convert::toString(y2);
	element->SetAttribute("d", linePathData.c_str());
}

/// https://www.w3.org/TR/SVG11/shapes.html#PolylineElement
void SvgDocument::convertPolylineToPath(XMLElement *element) {
	char *pointsString = element->Attribute("points");

	std::vector<std::string> pointData = getTokenList(pointsString, string() + NUMBER_REGEX_STRING);
	if (pointData.size() < 2) {
		throw ParseException(string() + "convertPolylineToPath: Too few points.");
	}

	// Set the data of the line path
	string linePathData = string() + "M " + pointData.at(0) + "," + pointData.at(1) + " L";
	for (size_t i = 0; i < pointData.size()-1; i += 2) {
		linePathData += string() + " " + pointData.at(2*i) + "," + pointData.at(2*i+1);
	}
	element->SetAttribute("d", linePathData.c_str());

	// Delete old data
	element->SetName("path");
	element->DeleteAttribute("points");
}

/// https://www.w3.org/TR/SVG11/shapes.html#PolygonElement
void SvgDocument::convertPolygonToPath(XMLElement *element) {
	convertPolylineToPath(element);
	string linePathData = string() + element->Attribute("d") + " Z";
	element->SetAttribute("d", linePathData.c_str());
}


MeshDataPtr SvgDocument::getMeshForDocument() {
	return root->getElementMesh();
}

MeshDataPtr SvgDocument::getMeshForElement(const string &elementID) {
	SvgElement *element = getSvgElementByID(elementID);
	return element->getElementMesh();
}

AABB2 SvgDocument::estimateElementAABB(XMLElement *svgElement) {
	return root; // TODO
}

void SvgDocument::indexSvgElement(SvgElement *element, const string &id) {
	elementMap.insert(make_pair(id, element));
}

SvgElement *SvgDocument::getSvgElementByID(const string &id) {
	return elementMap.find(id)->second;
}

