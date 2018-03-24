/*
 * Material.hpp
 *
 *  Created on: 15.03.2018
 *      Author: christoph
 */

#ifndef MESH_MATERIAL_HPP_
#define MESH_MATERIAL_HPP_

#include <boost/shared_ptr.hpp>
#include <Graphics/Color.hpp>
#include <XML/XML.hpp>

class Material;
typedef boost::shared_ptr<Material> MaterialPtr;

/**
 * A material specifices a color and optionally a texture (filename can be left empty if not needed).
 * Furthermore, if a texture file is set, one can also specify (see https://www.khronos.org/opengl/wiki/Sampler_Object):
 *  - The texture minification and magnification filters
 *  - The texture wrap mode
 */
struct Material  {
	bool equals(MaterialPtr material);
	void serializeXML(XMLPrinter *printer);

	Color color;
	/// "linear", "nearest", "linear mipmap" (== GL_LINEAR_MIPMAP_LINEAR), "nearest mipmap" (== GL_NEAREST_MIPMAP_NEAREST)
	string textureFilename;
	string textureMinFilter;
	string textureMagFilter;
	string textureWrap; ///< "repeat", "mirrored" (== mirrored repeat) or "clamp" (== clamp to edge)
};

#endif /* MESH_MATERIAL_HPP_ */
