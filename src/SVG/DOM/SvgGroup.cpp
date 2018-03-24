/*
 * SvgGroup.cpp
 *
 *  Created on: 19.03.2018
 *      Author: christoph
 */

#include "SvgGroup.hpp"
#include "SvgPath.hpp"

SvgGroup::~SvgGroup() {
	for (SvgElement *child : children) {
		delete child;
	}
	children.clear();
}

void SvgGroup::parseDocument(SvgDocument *doc, SvgGroup *parent, XMLElement *xmlElement) {
	SvgElement::parseDocument(doc, parent, xmlElement);

	for (XMLIterator it(xmlElement); it.isValid(); ++it) {
		XMLElement *subElement = *it;
		if (strcmp(subElement->Name(), "g") == 0) {
			SvgGroup *subGroup = new SvgGroup;
			subGroup->parseDocument(doc, this, subElement);
			children.push_back(subGroup);
		} else if (strcmp(subElement->Name(), "path") == 0) {
			SvgPath *subPath = new SvgPath;
			subPath->parseDocument(doc, this, subElement);
			children.push_back(subPath);
		}
	}
}

MeshDataPtr SvgGroup::getElementMesh() {
	MeshDataPtr meshData(new MeshData);

	// Traverse all child elements
	for (XMLIterator it(groupElement); it.isValid(); ++it) {
		XMLElement* svgElement = *it;
		if (svgElement->Attribute("id") && strcmp(svgElement->Name(), "g") == 0) {
			MeshDataPtr pathMesh = getMeshForGroup(svgElement);
			meshData = joinMeshes(meshData, pathMesh); // Merge?
		} else if (svgElement->Attribute("id") && strcmp(svgElement->Name(), "path") == 0) {
			MeshDataPtr pathMesh = getMeshForPath(svgElement);
			meshData = joinMeshes(meshData, pathMesh); // Merge?
		}
	}

	return meshData;
}
