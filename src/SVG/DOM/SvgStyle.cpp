/*
 * SvgStyle.cpp
 *
 *  Created on: 19.03.2018
 *      Author: christoph
 */

#include <vector>
#include <string>
#include <SVG/Parse/Tokens.hpp>
#include "SvgStyle.hpp"

static vector<string> styleKeyNames = {"font", "font-family", "font-size", "font-size-adjust", "font-stretch",
		"font-style", "font-variant", "font-weight", "direction", "letter-spacing", "text-decoration",
		"unicode-bidi", "word-spacing", "clip", "color", "cursor", "display", "overflow", "visibility",
		"clip-path", "clip-rule", "mask", "opacity", "enable-background", "filter", "flood-color",
		"flood-opacity", "lighting-color", "stop-color", "stop-opacity", "pointer-events", "color-interpolation",
		"color-interpolation-filters", "color-profile", "color-rendering", "fill", "fill-opacity",
		"fill-rule", "image-rendering", "marker", "marker-end", "marker-mid", "marker-start", "shape-rendering",
		"stroke", "stroke-dasharray", "stroke-dashoffset", "stroke-linecap", "stroke-linejoin",
		"stroke-miterlimit", "stroke-opacity", "stroke-width", "text-rendering", "alignment-baseline",
		"baseline-shift", "dominant-baseline", "glyph-orientation-horizontal", "glyph-orientation-vertical",
		"kerning", "text-anchor", "writing-mode"};


Constructor::Constructor() {
}

/**
 * A style string consists of "key:value" pairs seperated by semicolons.
 * @param styleString: The string to parse.
 * @return The key-value map.
 */
map<string, string> parseStyleString(const string &styleString) {
	getTokenList(transformContent, NUMBER_REGEX_STRING);
}

// Adds the value of "svgElement"'s attribute "name" to "styleMap"
void addOptionalAttributeToMap(const char *name, XMLElement *svgElement, map<string, string> &styleMap)
{
	const char *attribute;
	attribute = svgElement->Attribute(name);
	if (attribute) styleMap.insert(make_pair(name, attribute));
}


void SvgStyle::initStyleMap(SvgStyle *parentStyle, SvgElement *element)
{
	string pathStyle = getPathStyleString(svgElement);
	vector<string> styleDataList;
	StringMethods::get()->split(pathStyle.c_str(), ';', styleDataList);
	for (auto it = styleDataList.begin(); it != styleDataList.end(); ++it) {
		vector<string> styleData;
		StringMethods::get()->split(it->c_str(), ':', styleData);

		string first = styleData.at(0), second = styleData.at(1);
		first = StringMethods::get()->trim(first.c_str());
		second = StringMethods::get()->trim(second.c_str());
		styleMap.insert(make_pair(first, second));
	}

	for (const char *styleKey : styleKeyNames) {
		addOptionalAttributeToMap(styleKey, svgElement, styleMap);
	}

	// The path style overrides the style settings of its parent objects.
	XMLElement *parent = static_cast<XMLElement*>(svgElement->Parent());
	if (parent) getPathStyleMap(parent, styleMap);
}

Color SvgFile::getPathColor(const map<string, string> &styleMap, const string &fillOrStroke)
{
	Color color;
	auto it = styleMap.find(fillOrStroke);
	if (it != styleMap.end()) {
		if (it->second != "none") {
			if (StringMethods::get()->startsWith(it->second.c_str(), "rgb")) {
				vector<string> parts;
				StringMethods::get()->split(it->second.c_str(), " \t,", parts);
				color = Color(Convert::fromString<int>(parts.at(0)),
						Convert::fromString<int>(parts.at(1)), Convert::fromString<int>(parts.at(2)));
			} else {
				string hexValue = it->second.substr(1);
				color = colorFromHex(hexValue);
			}
		}
	}

	it = styleMap.find(fillOrStroke + "-opacity");
	if (it != styleMap.end()) {
		uint32_t alpha = color.getA();
		color.setA((int)(Convert::fromString<float>(it->second)*alpha));
	}

	return color;
}

FillRule SvgFile::getPathFillRule(const map<string, string> &styleMap)
{
	auto it = styleMap.find("fill-rule");
	if (it != styleMap.end()) {
		string fillRuleString = it->second;
		FillRule fillRule = FILL_RULE_NON_ZERO;
		if (fillRuleString == "nonzero") {
			fillRule = FILL_RULE_NON_ZERO;
		} else if (fillRuleString == "evenodd") {
			fillRule = FILL_RULE_EVEN_ODD;
		} else {
			Logfile::get()->writeError("ERROR: SvgFile::getPathFillRule: Unknown fill rule!");
		}
		return fillRule;
	}
	return FILL_RULE_NON_ZERO;
}

float SvgFile::getPathStrokeWidth(const map<string, string> &styleMap)
{
	auto it = styleMap.find("stroke-width");
	if (it != styleMap.end()) {
		return Convert::fromString<float>(it->second);
	}
	return 0.0f;
}
