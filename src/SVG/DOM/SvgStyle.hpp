/*
 * SvgStyle.hpp
 *
 *  Created on: 16.03.2018
 *      Author: christoph
 */

#ifndef SVG_DOM_SVGSTYLE_HPP_
#define SVG_DOM_SVGSTYLE_HPP_

#include <map>
#include <string>
#include <Graphics/Color.hpp>

using namespace std;

/**
 * https://www.w3.org/TR/SVG11/painting.html#FillProperties
 */
enum FillRule {
	FILL_RULE_NON_ZERO, FILL_RULE_EVEN_ODD
};

/**
 * https://www.w3.org/TR/SVG11/painting.html#SpecifyingPaint
 */
enum PaintType {
	PAINT_TYPE_COLOR, PAINT_TYPE_GRADIENT, PAINT_TYPE_NONE
};

class SvgPaintFill {
public:
	virtual ~SvgPaintFill() {}
	virtual PaintType getType()=0;

	FillRule fillRule;
};

class SvgPaintFillColor {
public:
	virtual ~SvgPaintFillColor() {}
	virtual PaintType getType() { return PAINT_TYPE_COLOR; };

	Color color;
};

class SvgPaintFillGradient {
public:
	virtual ~SvgPaintFillGradient() {}
	virtual PaintType getType() { return PAINT_TYPE_GRADIENT; };

	string gradientID;
};

class SvgPaintFillNone {
public:
	virtual ~SvgPaintFillNone() {}
	virtual PaintType getType() { return PAINT_TYPE_NONE; };
};

class SvgPaintStroke {
public:
	virtual ~SvgPaintStroke() {}
	virtual PaintType getType()=0;

	FillRule fillRule;
};

class SvgPaintStrokeColor {
public:
	virtual ~SvgPaintStrokeColor() {}
	virtual PaintType getType() { return PAINT_TYPE_COLOR; };

	Color color;
};

class SvgPaintStrokeGradient {
public:
	virtual ~SvgPaintStrokeGradient() {}
	virtual PaintType getType() { return PAINT_TYPE_GRADIENT; };

	string gradientID;
};

class SvgPaintStrokeNone {
public:
	virtual ~SvgPaintStrokeNone() {}
	virtual PaintType getType() { return PAINT_TYPE_NONE; };
};

class SvgElement;

/**
 * https://www.w3.org/TR/SVG11/styling.html#SVGStylingProperties
 */
struct SvgStyle {
public:
	void initStyleMap(SvgStyle *parentStyle, SvgElement *element);

	bool hasFill();
	FillRule getFillRule(); ///< non zero or even odd
	PaintType getFillType(); ///< plain color, gradient or blurred element (?)
	Color getFillColor();

	bool hasStroke();
	float getStrokeWidth();
	PaintType getStrokeType();
	Color getStrokeColor();


	/// A key-value map of all style properties (see link above)
	map<string, string> styleMap;

	Color fillColor;
	FillRule fillRule;
	float strokeWidth;
	float strokeColor;
};

#endif /* SVG_DOM_SVGSTYLE_HPP_ */
