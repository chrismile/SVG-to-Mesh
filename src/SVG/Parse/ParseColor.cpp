/*
 * ParseColor.cpp
 *
 *  Created on: 16.03.2018
 *      Author: christoph
 */

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/regex.hpp>
#include <Utils/Convert.hpp>
#include <Utils/StringUtils.hpp>
#include "ParseException.hpp"
#include "ParseColor.hpp"

/**
 * https://www.w3.org/TR/SVG/types.html#ColorKeywords
 * Predefined colors of the SVG specification.
 */
static std::map<std::string, Color> predefinedColorsMap = {
	{"aliceblue", Color(240, 248, 255)},
	{"antiquewhite", Color(250, 235, 215)},
	{"aqua", Color( 0, 255, 255)},
	{"aquamarine", Color(127, 255, 212)},
	{"azure", Color(240, 255, 255)},
	{"beige", Color(245, 245, 220)},
	{"bisque", Color(255, 228, 196)},
	{"black", Color( 0, 0, 0)},
	{"blanchedalmond", Color(255, 235, 205)},
	{"blue", Color( 0, 0, 255)},
	{"blueviolet", Color(138, 43, 226)},
	{"brown", Color(165, 42, 42)},
	{"burlywood", Color(222, 184, 135)},
	{"cadetblue", Color( 95, 158, 160)},
	{"chartreuse", Color(127, 255, 0)},
	{"chocolate", Color(210, 105, 30)},
	{"coral", Color(255, 127, 80)},
	{"cornflowerblue", Color(100, 149, 237)},
	{"cornsilk", Color(255, 248, 220)},
	{"crimson", Color(220, 20, 60)},
	{"cyan", Color( 0, 255, 255)},
	{"darkblue", Color( 0, 0, 139)},
	{"darkcyan", Color( 0, 139, 139)},
	{"darkgoldenrod", Color(184, 134, 11)},
	{"darkgray", Color(169, 169, 169)},
	{"darkgreen", Color( 0, 100, 0)},
	{"darkgrey", Color(169, 169, 169)},
	{"darkkhaki", Color(189, 183, 107)},
	{"darkmagenta", Color(139, 0, 139)},
	{"darkolivegreen", Color( 85, 107, 47)},
	{"darkorange", Color(255, 140, 0)},
	{"darkorchid", Color(153, 50, 204)},
	{"darkred", Color(139, 0, 0)},
	{"darksalmon", Color(233, 150, 122)},
	{"darkseagreen", Color(143, 188, 143)},
	{"darkslateblue", Color( 72, 61, 139)},
	{"darkslategray", Color( 47, 79, 79)},
	{"darkslategrey", Color( 47, 79, 79)},
	{"darkturquoise", Color( 0, 206, 209)},
	{"darkviolet", Color(148, 0, 211)},
	{"deeppink", Color(255, 20, 147)},
	{"deepskyblue", Color( 0, 191, 255)},
	{"dimgray", Color(105, 105, 105)},
	{"dimgrey", Color(105, 105, 105)},
	{"dodgerblue", Color( 30, 144, 255)},
	{"firebrick", Color(178, 34, 34)},
	{"floralwhite", Color(255, 250, 240)},
	{"forestgreen", Color( 34, 139, 34)},
	{"fuchsia", Color(255, 0, 255)},
	{"gainsboro", Color(220, 220, 220)},
	{"ghostwhite", Color(248, 248, 255)},
	{"gold", Color(255, 215, 0)},
	{"goldenrod", Color(218, 165, 32)},
	{"gray", Color(128, 128, 128)},
	{"grey", Color(128, 128, 128)},
	{"green", Color( 0, 128, 0)},
	{"greenyellow", Color(173, 255, 47)},
	{"honeydew", Color(240, 255, 240)},
	{"hotpink", Color(255, 105, 180)},
	{"indianred", Color(205, 92, 92)},
	{"indigo", Color( 75, 0, 130)},
	{"ivory", Color(255, 255, 240)},
	{"khaki", Color(240, 230, 140)},
	{"lavender", Color(230, 230, 250)},
	{"lavenderblush", Color(255, 240, 245)},
	{"lawngreen", Color(124, 252, 0)},
	{"lemonchiffon", Color(255, 250, 205)},
	{"lightblue", Color(173, 216, 230)},
	{"lightcoral", Color(240, 128, 128)},
	{"lightcyan", Color(224, 255, 255)},
	{"lightgoldenrodyellow", Color(250, 250, 210)},
	{"lightgray", Color(211, 211, 211)},
	{"lightgreen", Color(144, 238, 144)},
	{"lightgrey", Color(211, 211, 211)},
	{"lightpink", Color(255, 182, 193)},
	{"lightsalmon", Color(255, 160, 122)},
	{"lightseagreen", Color( 32, 178, 170)},
	{"lightskyblue", Color(135, 206, 250)},
	{"lightslategray", Color(119, 136, 153)},
	{"lightslategrey", Color(119, 136, 153)},
	{"lightsteelblue", Color(176, 196, 222)},
	{"lightyellow", Color(255, 255, 224)},
	{"lime", Color( 0, 255, 0)},
	{"limegreen", Color( 50, 205, 50)},
	{"linen", Color(250, 240, 230)},
	{"magenta", Color(255, 0, 255)},
	{"maroon", Color(128, 0, 0)},
	{"mediumaquamarine", Color(102, 205, 170)},
	{"mediumblue", Color( 0, 0, 205)},
	{"mediumorchid", Color(186, 85, 211)},
	{"mediumpurple", Color(147, 112, 219)},
	{"mediumseagreen", Color( 60, 179, 113)},
	{"mediumslateblue", Color(123, 104, 238)},
	{"mediumspringgreen", Color( 0, 250, 154)},
	{"mediumturquoise", Color( 72, 209, 204)},
	{"mediumvioletred", Color(199, 21, 133)},
	{"midnightblue", Color( 25, 25, 112)},
	{"mintcream", Color(245, 255, 250)},
	{"mistyrose", Color(255, 228, 225)},
	{"moccasin", Color(255, 228, 181)},
	{"navajowhite", Color(255, 222, 173)},
	{"navy", Color( 0, 0, 128)},
	{"oldlace", Color(253, 245, 230)},
	{"olive", Color(128, 128, 0)},
	{"olivedrab", Color(107, 142, 35)},
	{"orange", Color(255, 165, 0)},
	{"orangered", Color(255, 69, 0)},
	{"orchid", Color(218, 112, 214)},
	{"palegoldenrod", Color(238, 232, 170)},
	{"palegreen", Color(152, 251, 152)},
	{"paleturquoise", Color(175, 238, 238)},
	{"palevioletred", Color(219, 112, 147)},
	{"papayawhip", Color(255, 239, 213)},
	{"peachpuff", Color(255, 218, 185)},
	{"peru", Color(205, 133, 63)},
	{"pink", Color(255, 192, 203)},
	{"plum", Color(221, 160, 221)},
	{"powderblue", Color(176, 224, 230)},
	{"purple", Color(128, 0, 128)},
	{"red", Color(255, 0, 0)},
	{"rosybrown", Color(188, 143, 143)},
	{"royalblue", Color( 65, 105, 225)},
	{"saddlebrown", Color(139, 69, 19)},
	{"salmon", Color(250, 128, 114)},
	{"sandybrown", Color(244, 164, 96)},
	{"seagreen", Color( 46, 139, 87)},
	{"seashell", Color(255, 245, 238)},
	{"sienna", Color(160, 82, 45)},
	{"silver", Color(192, 192, 192)},
	{"skyblue", Color(135, 206, 235)},
	{"slateblue", Color(106, 90, 205)},
	{"slategray", Color(112, 128, 144)},
	{"slategrey", Color(112, 128, 144)},
	{"snow", Color(255, 250, 250)},
	{"springgreen", Color( 0, 255, 127)},
	{"steelblue", Color( 70, 130, 180)},
	{"tan", Color(210, 180, 140)},
	{"teal", Color( 0, 128, 128)},
	{"thistle", Color(216, 191, 216)},
	{"tomato", Color(255, 99, 71)},
	{"turquoise", Color( 64, 224, 208)},
	{"violet", Color(238, 130, 238)},
	{"wheat", Color(245, 222, 179)},
	{"white", Color(255, 255, 255)},
	{"whitesmoke", Color(245, 245, 245)},
	{"yellow", Color(255, 255, 0)},
	{"yellowgreen", Color(154, 205, 50)}
};


/* See: https://www.w3.org/TR/css-color-3/#rgba-color
 * Older SVG versions only supports a subset: https://www.w3.org/TR/SVG/types.html#DataTypeColor
 * This function also supports RGBA hexadecimal RGBA colors, which are do not conform to the specification
 * 1. #rrggbb or #rgb with hexdigits
 * 2. #rrggbbaa or #rgba with hexdigits
 * 3. rgb(r, g, b) with RGB values in the range 0-255
 * 4. rgba(r, g, b, a) with RGB integer values in the range 0-255, A in the range 0.0-1.0
 * 5. rgb(r%, g%, b%) with RGB values in the range 0%-100%
 * 6. rgba(r%, g%, b%, a) with RGB integer values in the range 0%-100%, A in the range 0.0-1.0
 * 7. Special color keywords
 */
Color parseCSS3ColorString(std::string colorString) {
	boost::trim(colorString);

	// Case 1: Hexadecimal color string
	if (boost::starts_with(colorString, "#")) {
		if (colorString.length() == 4) {
			// Case 1.1: #rgb
			uint8_t r = Convert::numFromHexString<uint32_t>(colorString.substr(1, 2));
			uint8_t g = Convert::numFromHexString<uint32_t>(colorString.substr(2, 2));
			uint8_t b = Convert::numFromHexString<uint32_t>(colorString.substr(3, 2));
			return Color(r + 256*r, g + 256*g, b + 256*b);
		} else if (colorString.length() == 5) {
			// Case 2.1: #rgba
			uint8_t r = Convert::numFromHexString<uint32_t>(colorString.substr(1, 2));
			uint8_t g = Convert::numFromHexString<uint32_t>(colorString.substr(2, 2));
			uint8_t b = Convert::numFromHexString<uint32_t>(colorString.substr(3, 2));
			uint8_t a = Convert::numFromHexString<uint32_t>(colorString.substr(4, 2));
			return Color(r + 256*r, g + 256*g, b + 256*b, a + 256*a);
		} else if (colorString.length() == 7) {
			// Case 1.2: #rrggbb
			uint8_t r = Convert::numFromHexString<uint32_t>(colorString.substr(1, 2));
			uint8_t g = Convert::numFromHexString<uint32_t>(colorString.substr(3, 2));
			uint8_t b = Convert::numFromHexString<uint32_t>(colorString.substr(5, 2));
			return Color(r, g, b);
		} else if (colorString.length() == 9) {
			// Case 2.2: #rgba
			uint8_t r = Convert::numFromHexString<uint32_t>(colorString.substr(1, 2));
			uint8_t g = Convert::numFromHexString<uint32_t>(colorString.substr(3, 2));
			uint8_t b = Convert::numFromHexString<uint32_t>(colorString.substr(5, 2));
			uint8_t a = Convert::numFromHexString<uint32_t>(colorString.substr(7, 2));
			return Color(r, g, b, a);
		}
	} else if (boost::starts_with(colorString, "rgb")) {
		std::string s = "\\s*", d = "(\\d+)", dp = "(\\d+)%";
		boost::regex rgbExpression(string() + "rgb\\s*\\(" + s + d + s + "," + s + d + s + "," + s + d + s + "\\)");
		boost::regex rgbaExpression(string() + "rgba\\s*\\(" + s + d + s + "," + s + d + s + "," + s + d + s + "," + s + "((\\.\\d*)?)\\s*\\)");
		boost::regex rgbExpressionPercent(string() + "rgb\\s*\\(" + s + dp + s + "," + s + dp + s + "," + s + dp + s + "\\)");
		boost::regex rgbaExpressionPercent(string() + "rgba\\s*\\(" + s + dp + s + "," + s + dp + s + "," + s + dp + s + "," + s + "((\\.\\d*)?)\\s*\\)");
		boost::cmatch what;
		if(boost::regex_match(colorString.c_str(), what, rgbExpression)) {
			// Case 3. rgb(r, g, b)
			uint32_t r = Convert::fromString<uint32_t>(what[1]);
			uint32_t g = Convert::fromString<uint32_t>(what[2]);
			uint32_t b = Convert::fromString<uint32_t>(what[3]);
			return Color(r, g, b);
		} else if (boost::regex_match(colorString.c_str(), what, rgbaExpression)) {
			// Case 4. rgba(r, g, b, a)
			uint32_t r = Convert::fromString<uint32_t>(what[1]);
			uint32_t g = Convert::fromString<uint32_t>(what[2]);
			uint32_t b = Convert::fromString<uint32_t>(what[3]);
			uint32_t a = Convert::fromString<float>(what[4]) * 255.0;
			return Color(r, g, b, a);
		} else if (boost::regex_match(colorString.c_str(), what, rgbExpressionPercent)) {
			// Case 5. rgb(r%, g%, b%)
			uint32_t r = Convert::fromString<uint32_t>(what[1]) / 100.0 * 255.0;
			uint32_t g = Convert::fromString<uint32_t>(what[2]) / 100.0 * 255.0;
			uint32_t b = Convert::fromString<uint32_t>(what[3]) / 100.0 * 255.0;
			return Color(r, g, b);
		} else if (boost::regex_match(colorString.c_str(), what, rgbaExpressionPercent)) {
			// Case 6. rgba(r%, g%, b%, a)
			uint32_t r = Convert::fromString<uint32_t>(what[1]) / 100.0 * 255.0;
			uint32_t g = Convert::fromString<uint32_t>(what[2]) / 100.0 * 255.0;
			uint32_t b = Convert::fromString<uint32_t>(what[3]) / 100.0 * 255.0;
			uint32_t a = Convert::fromString<float>(what[4]) * 255.0;
			return Color(r, g, b, a);
		}
	} else {
		auto it = predefinedColorsMap.find(colorString);
		if (it != predefinedColorsMap.end()) {
			return it->second;
		}
	}

	throw ParseException("parseCSSColorString: Invalid format.");
}

/// Converts color to CSS3 compatible color string (alpha is treated as a special case in the range of 0.0-1.0)
std::string colorToCSS3String(const Color &color) {
	if (color.getA() != 255) {
		return std::string() + "rgba("
				+ Convert::toString(color.getR()) + ", "
				+ Convert::toString(color.getG()) + ", "
				+ Convert::toString(color.getB()) + ", "
				+ Convert::toString((color.getA() / 255.0)) + ")";
	} else {
		return std::string() + "rgb("
				+ Convert::toString(color.getR()) + ", "
				+ Convert::toString(color.getG()) + ", "
				+ Convert::toString(color.getB()) + ")";
	}
}

/// Converts color to CSS3 compatible color string (exception: if alpha != 100%: also converts alpha)
std::string colorToCSS3HexString(const Color &color) {
	uint32_t colorUint = *((uint32_t*)&color);
	std::string colorString = std::string() + "#" + Convert::numToHexString(colorUint);
	if (color.getA() == 255) {
		colorString = colorString.substr(0, 7);
	}
	return colorString;
}
