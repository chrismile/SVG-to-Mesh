/*
 * SvgDocument.hpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#ifndef SVG_DOM_SVGDOCUMENT_HPP_
#define SVG_DOM_SVGDOCUMENT_HPP_

#include <Math/AABB2.hpp>
#include <Mesh/MeshData.hpp>
#include <XML/XML.hpp>
#include "SvgElement.hpp"

/**
 * The main class for loading an SVG file.
 * Manages an 'SvgElement' tree internally representing the document structure.
 */
class SvgDocument {
	/// Initialization
	SvgDocument(const string &filename, const string &output);

	/// SVG document properties
	inline AABB2 getViewBox() { return viewBox; }

	MeshDataPtr getMeshForDocument();
	MeshDataPtr getMeshForElement(const string &elementID);
	AABB2 estimateElementAABB(XMLElement *svgElement);

	/// Interface for class 'SvgElement'
	void indexSvgElement(SvgElement *element, const string &id);

private:
	/**
	 * Preprocessing: https://www.w3.org/TR/SVG/shapes.html#PolylineElement
	 * Converts shapes to normal path elements (-> less cases for handling SVG elements).
	 */
	void convertShapesToPaths(XMLElement *element);
	void convertRectangleToPath(XMLElement *element);
	void convertCircleToPath(XMLElement *element);
	void convertEllipseToPath(XMLElement *element);
	void convertLineToPath(XMLElement *element);
	void convertPolylineToPath(XMLElement *element);
	void convertPolygonToPath(XMLElement *element);

	SvgElement *getSvgElementByID(const string &id);

private: // Data
	tinyxml2::XMLDocument document;
	AABB2 viewBox;
	XMLElement *svgNode; ///< Top level XML node of SVG document
	SvgElementPtr root; ///< Representing group containing all SVG elements
	map<string, SvgElement*> elementMap; ///< Contains an ID -> element map for the whole document
};

#endif /* SVG_DOM_SVGDOCUMENT_HPP_ */
