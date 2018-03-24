/*
 * SvgPath.cpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#include <Utils/Convert.hpp>
#include <SVG/Parse/ParsePath.hpp>
#include "SvgPath.hpp"

void SvgPath::parseDocument(SvgDocument *doc, SvgGroup *parent, XMLElement *xmlElement) {
	;
}

SubMeshDataPtr SvgFile::getSubMeshForPath(XMLElement *svgElement)
{
	PathDataPtr pathData = getPathData(svgElement);
	vector<Vector2> vertexData;
	triangulatePathComplex(pathData, vertexData);
	SubMeshDataPtr subMesh(new SubMeshData);
	indexTriangles(vertexData, subMesh->vertexData, subMesh->indexData);
	subMesh->vertexMode = VERTEX_MODE_TRIANGLES;

	string materialName = getElementName(svgElement) + "_material";
	MaterialDataPtr material(new MaterialData(materialName));
	material->setColor(pathData->fillColor);
	subMesh->setMaterial(material);

	return subMesh;
}

SubMeshDataPtr SvgFile::getSubMeshForPathOutline(XMLElement *svgElement)
{
	// Create a mesh that shall contain all outlines
	MeshDataPtr meshData(new MeshData);
	PathDataPtr pathData = getPathData(svgElement);

	// Convert all outlines (regardless of fill type) to solid triangles
	for (SubPath &subpath : pathData->subpathsLocalSpace) { // TODO
		vector<Vector2> vertexData;
		SvgStrokeLineCap lineCap = SVG_LINE_CAP_BUTT;
		SvgStrokeLineJoin lineJoin = SVG_LINE_JOIN_MITER;
		float miterLimit = 4.0f;
		auto itLineCap = pathData->style.find("stroke-linecap");
		auto itLineJoin = pathData->style.find("stroke-linejoin");
		auto itMiterLimit = pathData->style.find("stroke-miterlimit");
		if (itLineCap != pathData->style.end()) {
			if (itLineCap->second == "butt")
				lineCap = SVG_LINE_CAP_BUTT;
			if (itLineCap->second == "round")
				lineCap = SVG_LINE_CAP_ROUND;
			if (itLineCap->second == "square")
				lineCap = SVG_LINE_CAP_SQUARE;
		}
		if (itLineJoin != pathData->style.end()) {
			if (itLineJoin->second == "miter")
				lineJoin = SVG_LINE_JOIN_MITER;
			if (itLineJoin->second == "round")
				lineJoin = SVG_LINE_JOIN_ROUND;
			if (itLineJoin->second == "bevel")
				lineJoin = SVG_LINE_JOIN_BEVEL;
		}
		if (itMiterLimit != pathData->style.end()) {
			miterLimit = Convert::fromString<float>(itMiterLimit->second);
		}
		computePathOutline(subpath.points, vertexData, pathData->strokeWidth, subpath.closed, lineCap, lineJoin, miterLimit);

		for (Vector2 &vert : vertexData) {
			vert = pathData->fullTransform * vert;
		}

		SubMeshDataPtr subMesh(new SubMeshData);
		indexTriangles(vertexData, subMesh->vertexData, subMesh->indexData);
		subMesh->vertexMode = VERTEX_MODE_TRIANGLES;

		string elementName = getElementName(svgElement);
		MaterialDataPtr material(new MaterialData(elementName));
		material->setColor(pathData->strokeColor);
		subMesh->setMaterial(material);
		meshData->addSubMesh(subMesh);
	}

	// Merge the submeshes of the outlines and return the resulting mesh
	MeshDataPtr mergedMesh = mergeSubMeshes(meshData->getSubMeshes());
	return mergedMesh->getSubMesh(0);
}

MeshDataPtr SvgPath::getElementMesh() {
	// Step 1: Is the element blurred or does it have a color gradient?
	XMLElement *blurFilterElement = getBlurFilterElement(pathElement);
	XMLElement *gradientElement = getGradientElement(pathElement, false);
	XMLElement *strokeGradientElement = getGradientElement(pathElement, true);
	if (blurFilterElement) {
		// Blur filter. Rasterize the element and blur it. Add the result as a texture-mapped rectangle!
		string blurName = string() + outputMeshName + "_blur" + Convert::toString(blurNumber);
		string bitmapFilename = outputDirectory + blurName + ".png";
		meshData->addSubMesh(createBlurredElement(this, pathElement, blurFilterElement, bitmapFilename.c_str(), blurName.c_str()));
		++blurNumber;
	} else {
		// Step 2: Convert the path and the outline to a submesh
		PathDataPtr pathData = getPathData(pathElement);

		// Is the path filled?
		if (pathData->style.find("fill") != pathData->style.end() && pathData->style["fill"] != "none") {
			SubMeshDataPtr subMesh = getSubMeshForPath(pathElement);
			meshData->addSubMesh(subMesh);

			// If a gradient is set, render it to a bitmap and use UV-mapping
			if (gradientElement) {
				string gradientName = string() + outputMeshName + "_gradient" + Convert::toString(gradientNumber);
				string bitmapFilename = outputDirectory + gradientName + ".png";
				createGradientBitmap(this, pathElement, subMesh, gradientElement, bitmapFilename.c_str(), gradientName.c_str(), false);
				++gradientNumber;
			}

			// If you want the path to be textured using edge gradients, assign a checkerboard pattern to it.
			if (pathData->style["fill"] == "url(#Checkerboard)" || StringMethods::get()->contains(pathData->style["fill"].c_str(), "pattern")) {
				string fillName = string() + outputMeshName + "_gradient" + Convert::toString(gradientNumber);
				string bitmapFilename = outputDirectory + fillName + ".png";
				Color colorBorder(0, 92, 150, 255), colorInside(83, 133, 225, 255);

				if (Settings::get()->getValue("border-color").length() > 0) {
					colorBorder = Settings::get()->getColorValue("border-color");
				}
				if (Settings::get()->getValue("inside-color").length() > 0) {
					colorInside = Settings::get()->getColorValue("inside-color");
				}

				createEdgeGradientTexture(this, pathData, subMesh, bitmapFilename.c_str(), fillName.c_str(), colorBorder, colorInside);
				++gradientNumber;
			}
		}

		// Is an outline set?
		if (pathData->strokeWidth > 0.0f && pathData->style.find("stroke") != pathData->style.end() && pathData->style["stroke"] != "none") {
			SubMeshDataPtr subMesh = getSubMeshForPathOutline(pathElement);
			meshData->addSubMesh(subMesh);

			// If a gradient is set, render it to a bitmap and use UV-mapping
			if (strokeGradientElement) {
				string gradientName =  string() + outputMeshName + "_gradient" + Convert::toString(gradientNumber);
				string bitmapFilename = outputDirectory + gradientName + ".png";
				createGradientBitmap(this, pathElement, subMesh, strokeGradientElement, bitmapFilename.c_str(), gradientName.c_str(), true);
				++gradientNumber;
			}

		}
	}
	return meshData;
}

void SvgPath::createPathData() {
	assert(xmlElement->Attribute("d") != NULL);
	vector<string> pathDataList = splitPathString(xmlElement->Attribute("d"));

	vector<Vector2> pointList;
	char command = 'm';
	Vector2 point, last;
	for (auto it = pathDataList.begin(); it != pathDataList.end(); ++it)
	{
		// Do we currently have a command?
		if (*it == "M" || *it == "m" || *it == "C" || *it == "c" || *it == "S" || *it == "s" || *it == "Q"
				|| *it == "q" || *it == "T" || *it == "t" || *it == "A" || *it == "a" || *it == "L" || *it == "l") {
			command = (*it).at(0);
			continue;
		} else if (*it == "Z" || *it == "z") {
			// The current subpath will be closed
			pathData->subpaths.push_back(SubPath());
			pathData->subpaths.back().closed = true;
			pathData->subpaths.back().points = pointList;
			pointList.clear();

			// Add the first point of the last subpath to the list if we don't have 'M' or 'm' as the next command
			// See http://www.w3.org/TR/SVG/paths.html#PathDataClosePathCommand for further details
			auto nextIt = it; ++nextIt;
			if (nextIt != pathDataList.end()) {
				if (*nextIt == "m") {
					// In this case the next path starts relative to this one
					// => Set the first point of the new subpath manually!
					command = 'm';
					++it; auto it1 = ++it; auto it2 = ++it;
					point = Vector2(Convert::fromString<float>(it1->c_str()), Convert::fromString<float>(it2->c_str()));
					point += pathData->subpaths.back().points.front();
					pointList.push_back(point);
				} else if (*nextIt != "M") {
					// The new subpath starts with the last point of the previous subpath
					pointList.push_back(pathData->subpaths.back().points.front());
				}
			}
			continue;
		}


		// A point is created from the first two packets of data after the command because it is assumed that,
		// for each path command, first of all a point with two coordinates is given.
		// This removes the need for copy-pasting code for simple commands like 'm'.
		auto it1 = it; ++it;
		point = Vector2(Convert::fromString<float>(it1->c_str()), Convert::fromString<float>(it->c_str()));

		switch (command) {
		case 'T':
		case 'M': {
			pointList.push_back(point);
		} break;

		case 't':
		case 'm': {
			if (pointList.size() > 0) {
				point += pointList.back();
			}
			pointList.push_back(point);
		} break;

		case 'C': {
			Vector2 p1 = point; ++it;
			auto it1 = it; ++it;
			Vector2 p2 = Vector2(Convert::fromString<float>(it1->c_str()), Convert::fromString<float>(it->c_str()));
			++it; it1 = it; ++it;
			Vector2 p3 = Vector2(Convert::fromString<float>(it1->c_str()), Convert::fromString<float>(it->c_str()));

			vector<Vector2> bezierPoints;
			if (estimate) {
				getPointsOnCubicBezier(bezierPoints, getBezierSubdivision(), pointList.back(), p1, p2, p3);
			} else {
				getRecursivePointsOnCubicBezier(bezierPoints, pointList.back(), p1, p2, p3);
			}
			for (int i = 1; i < (int)bezierPoints.size(); ++i) {
				pointList.push_back(bezierPoints.at(i));
			}
		} break;

		case 'c': {
			Vector2 p1 = pointList.back() + point; ++it;
			auto it1 = it; ++it;
			Vector2 p2 = pointList.back() + Vector2(Convert::fromString<float>(it1->c_str()), Convert::fromString<float>(it->c_str()));
			++it; it1 = it; ++it;
			Vector2 p3 = pointList.back() + Vector2(Convert::fromString<float>(it1->c_str()), Convert::fromString<float>(it->c_str()));

			vector<Vector2> bezierPoints;
			//getPointsOnCubicBezier(bezierPoints, getBezierSubdivision(), pointList.back(), p1, p2, p3);
			if (estimate) {
				getPointsOnCubicBezier(bezierPoints, getBezierSubdivision(), pointList.back(), p1, p2, p3);
			} else {
				getRecursivePointsOnCubicBezier(bezierPoints, pointList.back(), p1, p2, p3);
			}
			for (int i = 1; i < (int)bezierPoints.size(); ++i) {
				pointList.push_back(bezierPoints.at(i));
			}
		} break;

		case 'Q':
		case 'S': {
			++it;
			auto it1 = it; ++it;
			point = Vector2(Convert::fromString<float>(it1->c_str()), Convert::fromString<float>(it->c_str()));
			pointList.push_back(point);
		} break;

		case 'q':
		case 's': {
			++it;
			auto it1 = it; ++it;
			point = Vector2(Convert::fromString<float>(it1->c_str()), Convert::fromString<float>(it->c_str()));

			if (pointList.size() > 0) {
				point += pointList.back();
			}
			pointList.push_back(point);
		} break;

		case 'A': {
			// rx,ry x-rot fa fs x,y
			Vector2 radius = point;

			++it;
			float xrot = Convert::fromString<float>(it->c_str());

			++it;
			int fa = Convert::fromString<int>(it->c_str());

			++it;
			int fs = Convert::fromString<int>(it->c_str());

			++it;
			auto it1 = it; ++it;
			point = Vector2(Convert::fromString<float>(it1->c_str()), Convert::fromString<float>(it->c_str()));
			Vector2 lastPoint = pointList.back();

			SvgEllipticalArcDataIn arcData(lastPoint.x, lastPoint.y, point.x, point.y, radius.x, radius.y, xrot, fa, fs);
			arcData.rx = radius.x;
			vector<Vector2> arcPoints;
			arcPoints.reserve(10);
			getPointsOnSvgEllipticalArc(arcPoints, arcData);
			for (int i = 1; i < (int)arcPoints.size(); ++i) {
				point = arcPoints.at(i);
				pointList.push_back(point);
			}
		} break;

		case 'a': {
			// rx,ry x-rot fa fs x,y
			Vector2 radius = point;

			++it;
			float xrot = Convert::fromString<float>(it->c_str());

			++it;
			int fa = Convert::fromString<int>(it->c_str());

			++it;
			int fs = Convert::fromString<int>(it->c_str());

			++it;
			auto it1 = it; ++it;
			point = Vector2(Convert::fromString<float>(it1->c_str()), Convert::fromString<float>(it->c_str()));
			Vector2 lastPoint = pointList.back();
			point += lastPoint;

			SvgEllipticalArcDataIn arcData(lastPoint.x, lastPoint.y, point.x, point.y, radius.x, radius.y, xrot, fa, fs);
			arcData.rx = radius.x;
			vector<Vector2> arcPoints;
			arcPoints.reserve(10);
			getPointsOnSvgEllipticalArc(arcPoints, arcData);
			for (int i = 1; i < (int)arcPoints.size(); ++i) {
				point = arcPoints.at(i);
				pointList.push_back(point);
			}
		} break;

		case 'L': {
			pointList.push_back(point);
		} break;

		case 'l': {
			if (pointList.size() > 0) {
				point += pointList.back();
			}
			pointList.push_back(point);
		} break;
		}
	}

	// Is the last subpath not closed and was it therefore not added?
	if (pointList.size() > 1) {
		pathData->subpaths.push_back(SubPath());
		pathData->subpaths.back().closed = false;
		pathData->subpaths.back().points = pointList;
		pointList.clear();
	}


	// Mirror the path, remove adjacent duplicate points and points on lines for the triangulator.
	for (SubPath &subpath : pathData->subpaths) {
		if (subpath.points.size() > 1) {
			mirrorPointsAroundXAxis(subpath.points);

			// No duplicate points at beginning and end!
			if (isApproximately(subpath.points.front(), subpath.points.back())) {
				subpath.points.pop_back();
				subpath.closed = true; // beginning equals end => actually a closed path!
			}

			removeDuplicatePoints(subpath.points);
			removePointsOnLine(subpath.points, subpath.closed);
		}
	}
}
