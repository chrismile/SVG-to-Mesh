/*
 * SubMeshData.cpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#include <XML/XML.hpp>
#include <Utils/Convert.hpp>
#include "Material.hpp"
#include "SubMeshData.hpp"

string vertexModeToString(VertexMode vertexMode) {
	switch(vertexMode) {
	case VERTEX_MODE_POINTS:
		return "points";
	case VERTEX_MODE_LINES:
		return "lines";
	case VERTEX_MODE_LINE_LOOP:
		return "line loop";
	case VERTEX_MODE_LINE_STRIP:
		return "line strip";
	case VERTEX_MODE_TRIANGLES:
		return "triangles";
	case VERTEX_MODE_TRIANGLE_STRIP:
		return "triangle strip";
	case VERTEX_TRIANGLE_FAN:
		return "triangle fan";
	default:
		return "Invalid";
	}
}

void SubMeshData::serializeXMLMesh(tinyxml2::XMLPrinter *printer) {
	assert(vertexData.size() == texCoordData.size() || texCoordData.size() == 0);

	printer->OpenElement("SubMesh");
	material->serializeXML(printer);

	// Add the vertices (positions and optionally texture coordinates)
	printer->OpenElement("VertexData");
	printer->PushAttribute("vertexmode", vertexModeToString(vertexMode).c_str());
	vector<Vector2>::iterator vertexIt = vertexData.begin(), texcoordIt = texCoordData.begin();
	while(vertexIt != vertexData.end() && texcoordIt != texCoordData.end()) {
		printer->OpenElement("Vertex");
		printer->PushAttribute("x", vertexIt->x);
		printer->PushAttribute("y", vertexIt->y);
		if (texcoordIt != texCoordData.end()) {
			printer->PushAttribute("u", texcoordIt->x);
			printer->PushAttribute("v", texcoordIt->y);
			++texcoordIt;
		}
		printer->CloseElement();
		++vertexIt;
	}
	printer->CloseElement();

	// Add index data
	if (indexData.size() > 0) {
		printer->OpenElement("Indices");

		if (indexData.size() > 65535) {
			printer->PushAttribute("use32bitindices", "true");
		}

		string indexDataString = "";
		indexDataString.reserve(indexData.size()*3); //< Rough estimate
		int i = 0;
		for (auto it = indexData.begin(); it != indexData.end(); ++it) {
			indexDataString += Convert::toString(*it);
			if (i != (int)indexData.size()-1) {
				indexDataString += " ";
			}
			++i;
		}

		if (indexDataString.length() > 0)
			printer->PushAttribute("data", indexDataString.c_str());

		printer->CloseElement();
	}


	printer->CloseElement();
}

AABB2 SubMeshData::computeAABB() {
	Vector2 min(FLT_MAX, FLT_MAX), max(-FLT_MAX, -FLT_MAX);
	for (const Vector2 &vec : vertexData) {
		if (vec.x < min.x)
			min.x = vec.x;
		if (vec.x > max.x)
			max.x = vec.x;
		if (vec.y < min.y)
			min.y = vec.y;
		if (vec.y > max.y)
			max.y = vec.y;
	}
	return AABB2(min, max);
}

void SubMeshData::setTexturedRectangle(const AABB2 &aabb) {
	// Vertices
	addPoint(Vector2(aabb.getMinimum().x, aabb.getMaximum().y));
	addPoint(Vector2(aabb.getMaximum().x, aabb.getMinimum().y));
	addPoint(Vector2(aabb.getMaximum().x, aabb.getMaximum().y));
	addPoint(Vector2(aabb.getMinimum().x, aabb.getMinimum().y));

	// Texture coordinates
	addTexCoord(Vector2(0.0f, 0.0f));
	addTexCoord(Vector2(1.0f, 1.0f));
	addTexCoord(Vector2(1.0f, 0.0f));
	addTexCoord(Vector2(0.0f, 1.0f));

	// Indices
	addIndex(0);
	addIndex(1);
	addIndex(2);
	addIndex(0);
	addIndex(3);
	addIndex(1);
}

