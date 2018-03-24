/*
 * MeshData.hpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#ifndef MESH_MESHDATA_HPP_
#define MESH_MESHDATA_HPP_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <Math/AABB2.hpp>

class MeshData;
typedef boost::shared_ptr<MeshData> MeshDataPtr;
class SubMeshData;
typedef boost::shared_ptr<SubMeshData> SubMeshDataPtr;

namespace tinyxml2 {
class XMLPrinter;
}

/**
 * A mesh is a collection of multiple submeshes.
 * This is necessary, as each submesh can only be associated with one material.
 * This restriction comes from the fact that low level graphics engines like OpenGL or DirectX
 * can normally only use one material per rendering call.
 */
class MeshData  {
public:
	/**
	 * Writes the mesh data to a file. See the accompanying documentation for more information on the format.
	 * @arg filename: The file to write the xml mesh to.
	 */
	bool writeXMLMeshToFile(const char *filename);

	/// Computes and returns the axis aligned bounding box in local coordinates
	AABB2 computeAABB();
	/// Transforms all submesh vertex positions using the passed matrix
	void transform(const Matrix3 &m);

	// Submeshes
	inline void addSubMesh(SubMeshDataPtr submesh) { submeshes.push_back(submesh); }
	inline std::vector<SubMeshDataPtr> &getSubMeshes() { return submeshes; }

private:
	void serializeXMLMesh(tinyxml2::XMLPrinter *output);
	std::vector<SubMeshDataPtr> submeshes; ///< The list of submeshes
};


#endif /* MESH_MESHDATA_HPP_ */
