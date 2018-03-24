/*
 * Material.cpp
 *
 *  Created on: 17.03.2018
 *      Author: christoph
 */

#include <SVG/Parse/ParseColor.hpp>
#include "Material.hpp"

bool Material::equals(MaterialPtr material) {
	return color == material->color && textureFilename == material->textureFilename;
}

void Material::serializeXML(XMLPrinter *printer) {
	std::string colorString = colorToCSS3String(color);

	printer->OpenElement("Material");
	printer->PushAttribute("color", colorString.c_str());

	// Is a texture set?
	if (textureFilename.size() > 0) {
		printer->PushAttribute("texture", textureFilename.c_str());

		// Assume standard values if not set (see documentation of file format)
		if (textureMinFilter.size() > 0) {
			printer->PushAttribute("minfilter", textureMinFilter.c_str());
		}
		if (textureMagFilter.size() > 0) {
			printer->PushAttribute("magfilter", textureMagFilter.c_str());
		}
		if (textureWrap.size() > 0) {
			printer->PushAttribute("wrapmode", textureWrap.c_str());
		}
	}
	printer->CloseElement();
}
