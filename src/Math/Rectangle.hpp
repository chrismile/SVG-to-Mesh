/*
 * Rectangle.hpp
 *
 *  Created on: 01.10.2016
 *      Author: Christoph Neuhausertoph
 */

#ifndef RECTANGLE_HPP_
#define RECTANGLE_HPP_

/**
 * A 2D rectangle specified by its lower left corner and its width and height.
 */
class Rectangle
{
public:
	float x, y, w, h;

	Rectangle () : x (0), y (0), w (0), h (0) { }
	Rectangle (float _x, float _y, float _w, float _h) : x (_x), y (_y), w (_w), h (_h) { }
	Rectangle (const Rectangle &rect) : x(rect.x), y(rect.y), w(rect.w), h(rect.h) {}

	/// Returns whether this rectangle and the passed one intersect
	bool intersects (const Rectangle &rect) const {
		if ( (y < rect.y + rect.h) && (y + h > rect.y) &&
			 (x < rect.x + rect.w) && (x + w > rect.x) ) {
			return true;
		}
		return false;
	}

	/// Returns whether this rectangle contains the passed one
	bool contains (const Rectangle &rect) const {
		if ( (rect.y >= y) && (rect.y + rect.h <= y + h) &&
			 (rect.x >= x) && (rect.x + w <= x + w) ) {
			return true;
		}
		return false;
	}
};

#endif /* RECTANGLE_HPP_ */
