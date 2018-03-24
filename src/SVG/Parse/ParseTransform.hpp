/*
 * ParseTransform.hpp
 *
 *  Created on: 17.03.2018
 *      Author: christoph
 */

#ifndef SVG_PARSE_PARSETRANSFORM_HPP_
#define SVG_PARSE_PARSETRANSFORM_HPP_

#include <XML/XML.hpp>
#include <Math/Matrix3.hpp>

/**
 * https://www.w3.org/TR/SVG11/coords.html#TransformAttribute
 * Parses the attribute "transform" of 'svgElement'.
 */
Matrix3 parseElementTransformMatrix(XMLElement *svgElement);

#endif /* SVG_PARSE_PARSETRANSFORM_HPP_ */
