/*
 * SvgGroup.hpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#ifndef SVG_DOM_SVGGROUP_HPP_
#define SVG_DOM_SVGGROUP_HPP_

#include <vector>
#include "SvgElement.hpp"

/**
 * https://www.w3.org/TR/SVG11/struct.html#Groups
 * "The 'g' element is a container element for grouping together related graphics elements."
 */
class SvgGroup : public SvgElement {
public:
	virtual ~SvgGroup();

	/**
	 * This function is called either by SvgDocument or by a parent SvgGroup.
	 * It reads all data from the XML document and creates child elements if necessary.
	 */
	virtual void parseDocument(SvgDocument *doc, SvgGroup *parent, XMLElement *xmlElement);

	/**
	 * Creates and returns a triangle mesh for this SVG element.
	 */
	virtual MeshDataPtr getElementMesh();

private:
	std::vector<SvgElement*> children;
};

#endif /* SVG_DOM_SVGGROUP_HPP_ */
