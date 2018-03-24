/*
 * Triangulation.hpp
 *
 *  Created on: 14.03.2018
 *      Author: christoph
 */

#ifndef SVG_GEOMETRY_TRIANGULATION_HPP_
#define SVG_GEOMETRY_TRIANGULATION_HPP_

#include <vector>
#include <Math/Vector2.hpp>

using namespace std;

/*
 * Converts the path to triangles, which are stored in "triangulatedVertices".
 * This is the simple version of the algorithm: It only supports convex and concave polygons
 * without self-intersection and without holes.
 * Currently, poly2tri is used as an implementation of Delaunay Triangulation.
 * @
 */
//void triangulatePathSimple(const vector<Vector2> &path, vector<Vector2> &triangulatedVertices);

/*
 * The more complex form of the algorithm:
 * "pathData" can contain multiple (convex/concave/self-intersecting) paths, which are
 * converted to triangles using the fill-rule of "pathData". So even complex polygons
 * with holes are supported thanks to the use of the polygon clipping library "Clipper".
 * http://angusj.com/delphi/clipper.php
 */
//void triangulatePathComplex(const SvgPathPtr pathData, vector<Vector2> &triangulatedVertices);

#endif /* SVG_GEOMETRY_TRIANGULATION_HPP_ */
