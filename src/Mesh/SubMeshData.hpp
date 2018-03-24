/*
 * SubMeshData.hpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#ifndef MESH_SUBMESHDATA_HPP_
#define MESH_SUBMESHDATA_HPP_

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <Math/Vector2.hpp>
#include <Math/AABB2.hpp>
#include <Graphics/Color.hpp>

class SubMeshData;
typedef boost::shared_ptr<SubMeshData> SubMeshDataPtr;
class Material;
typedef boost::shared_ptr<Material> MaterialPtr;

namespace tinyxml2 {
class XMLPrinter;
}

/**
 * The vertex mode determines how a stream of vertices is interpreted (e.g. points, lines, triangles).
 * Same values as OpenGL vertex modes.
 */
enum VertexMode {
	VERTEX_MODE_POINTS = 0x0000,
	VERTEX_MODE_LINES = 0x0001, VERTEX_MODE_LINE_LOOP = 0x0002, VERTEX_MODE_LINE_STRIP = 0x0003,
	VERTEX_MODE_TRIANGLES = 0x0004, VERTEX_MODE_TRIANGLE_STRIP = 0x0005, VERTEX_TRIANGLE_FAN = 0x0006
};

/// Converts a vertex mode object into a human readable form.
string vertexModeToString(VertexMode vertexMode);

/**
 * A sub mesh contains...
 *  - The vertex data (positions and texture coordinates) in local space
 *  - Optionally index data (for referencing recurring vertices)
 *  - A material (with an optional texture component)
 */
class SubMeshData  {
public:
private:
	friend class MeshData;

	SubMeshData() : vertexMode(VERTEX_MODE_TRIANGLES) {}
	void serializeXMLMesh(tinyxml2::XMLPrinter *output);

	// Adding vertices and accessing the material
	inline void addPoint(const Vector2 &point) { vertexData.push_back(point); }
	inline void addTexCoord(const Vector2 &texCoord) { texCoordData.push_back(texCoord); }
	inline void addIndex(unsigned short index) { indexData.push_back(index); }
	inline MaterialPtr getMaterial() const { return material; }
	inline void setMaterial(const MaterialPtr &mat) { material = mat; }

	/// Computes and returns the axis aligned bounding box in local coordinates
	AABB2 computeAABB();

	/**
	 * Auxiliary function: Sets the vertex, index and texture coordinate data to a textured
	 * rectangle (lower left corner: texture coords. (0,0), upper right corner: (1,1)).
	 * TODO: Order correct?
	 * @arg aabb: The rectangle in local coordinates.
	 */
	void setTexturedRectangle(const AABB2 &aabb);

	// ONLY DECLARED AS PUBLIC FOR EXTERN SERIALIZATION
	std::vector<Vector2> vertexData;
	std::vector<Vector2> texCoordData; ///< optional
	//std::vector<Color> colorData; ///< optional
	std::vector<unsigned int> indexData; ///< optional
	MaterialPtr material;
	VertexMode vertexMode;
};

#endif /* MESH_SUBMESHDATA_HPP_ */
