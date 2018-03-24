/*
 * SvgElement.cpp
 *
 *  Created on: 16.03.2018
 *      Author: christoph
 */

#include "SvgElement.hpp"


void SvgElement::parseDocument(SvgDocument *doc, SvgGroup *parent, XMLElement *xmlElement) {
	this->document = doc;
	this->parent = parent;
	this->xmlElement = xmlElement;

	// Initialize the style properties of the element (derived from its parent's style attributes)
	this->style.initStyleMap(parent->getStyle(), xmlElement);
}
