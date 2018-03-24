/*
 * SvgPath.hpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#ifndef SVG_DOM_SVGPATH_HPP_
#define SVG_DOM_SVGPATH_HPP_

#include <vector>
#include <Math/Vector2.hpp>
#include "SvgElement.hpp"

using namespace std;

/**
 * @file
 * https://www.w3.org/TR/SVG11/paths.html
 * "Paths represent the outline of a shape which can be filled, stroked, used as a clipping path, or any combination of the three."
 * A path (see @SvgPath) can have multiple subpaths (see @SubPath).
 */

class SubPath
{
public:
	SubPath() : closed(false) {}
	SubPath(bool _closed) : closed(_closed) {}
	vector<Vector2> points;
	bool closed;
};

class SvgPath  : public SvgElement {
public:
	virtual ~SvgPath() {}

	/**
	 * This function is called either by SvgDocument or by a parent SvgGroup.
	 * It reads all data from the XML document and creates child elements if necessary.
	 */
	virtual void parseDocument(SvgDocument *doc, SvgGroup *parent, XMLElement *xmlElement);

	/**
	 * Creates and returns a triangle mesh for this SVG element.
	 */
	virtual MeshDataPtr getElementMesh();

	/**
	 * Expects that 'parseDocument' was already called.
	 * Creates the path data for a path element or delegates the work to all children of a group.
	 */
	void createPathData();

private:
	// An SVG path can consist of multiple subpaths
	vector<SubPath> subpathsLocalSpace; ///< In local space
	vector<SubPath> subpathsGlobalSpace; ///< Path points in world space
};

#endif /* SVG_DOM_SVGPATH_HPP_ */
