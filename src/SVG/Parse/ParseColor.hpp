/*
 * ParseColor.hpp
 *
 *  Created on: 16.03.2018
 *      Author: christoph
 */

#ifndef SVG_PARSE_PARSECOLOR_HPP_
#define SVG_PARSE_PARSECOLOR_HPP_

#include <string>
#include <Graphics/Color.hpp>

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
Color parseCSS3ColorString(std::string colorString);

/// Converts color to CSS3 compatible color string (alpha is treated as a special case in the range of 0.0-1.0)
std::string colorToCSS3String(const Color &color);

/// Converts color to CSS3 compatible color string (exception: if alpha != 100%: also converts alpha)
std::string colorToCSS3HexString(const Color &color);


#endif /* SVG_PARSE_PARSECOLOR_HPP_ */
