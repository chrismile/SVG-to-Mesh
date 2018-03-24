/*
 * SvgElement.hpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#ifndef SVG_DOM_SVGELEMENT_HPP_
#define SVG_DOM_SVGELEMENT_HPP_

#include <boost/shared_ptr.hpp>
#include <Math/Matrix3.hpp>
#include <Math/AABB2.hpp>
#include <XML/XML.hpp>
#include "SvgStyle.hpp"

class SvgGroup;
class SvgDocument;
class SvgElement;
typedef boost::shared_ptr<SvgElement> SvgElementPtr;

class SvgElement {
public:
	SvgElement(SvgGroup *parent, XMLElement *xmlElement) : parent(parent), xmlElement(xmlElement) {}
	virtual ~SvgElement() {}

	/// @return: The parent SvgGroup of this element. Can be zero.
	inline SvgGroup *getParent() { return parent; }
	/// @return: The style attributes of this SVG element (@see SvgStyle)
	inline SvgStyle *getStyle() { return &style; }
	/// @return: The transform of the element's points or children relative to the document
	inline Matrix3 getGlobalTransform() { return globalTransform; }

	/**
	 * This function is called either by SvgDocument or by a parent SvgGroup.
	 * It reads all data from the XML document and creates child elements if necessary.
	 * Note: All subclasses should call the base implementation of SvgElement before doing anything else.
	 */
	virtual void parseDocument(SvgDocument *doc, SvgGroup *parent, XMLElement *xmlElement);

	/**
	 * Creates and returns a triangle mesh for this SVG element.
	 */
	virtual MeshDataPtr getElementMesh()=0;

private:
	SvgDocument *document;
	SvgGroup *parent;
	XMLElement *xmlElement;

	SvgStyle style; ///< The fill and stroke style of this element
	Matrix3 localTransform; ///< The transform of this element relative to its parent
	Matrix3 globalTransform; ///< The transform of this element relative to the document
	AABB2 localAABB; ///< AABB in local space
	AABB2 globalAABB; ///< AABB in document space
};

#endif /* SVG_DOM_SVGELEMENT_HPP_ */
