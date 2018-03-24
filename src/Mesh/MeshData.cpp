/*
 * MeshData.cpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#include <iostream>
#include <Math/Matrix3.hpp>
#include <Math/AABB2.hpp>
#include <XML/XML.hpp>
#include "SubMeshData.hpp"
#include "MeshData.hpp"

using namespace std;

bool MeshData::writeXMLMeshToFile(const char *filename) {
	FILE *file = fopen(filename, "w");

	if (file == NULL) {
		cerr << "ERROR: MeshData::serializeXMLMesh: Couldn't create file \"" << filename << "\"!" << endl;
		return false;
	}

	XMLPrinter printer(file);
	serializeXMLMesh(&printer);
	fclose(file);

	return true;
}

void MeshData::serializeXMLMesh(tinyxml2::XMLPrinter *printer) {
	printer->OpenElement("MeshXML");

	// Write the mesh data
	for (size_t i = 0; i < submeshes.size(); ++i) {
		submeshes.at(i)->serializeXMLMesh(printer);
	}

	// Close the document
	printer->CloseElement();
}

AABB2 MeshData::computeAABB() {
	AABB2 aabb;
	for (SubMeshDataPtr &submesh : submeshes) {
		aabb.combine(submesh->computeAABB());
	}
	return aabb;
}

void MeshData::transform(const Matrix3 &m) {
	for (SubMeshDataPtr &submesh : submeshes) {
		for (Vector2 &v : submesh->vertexData) {
			v = m * v;
		}
	}
}
