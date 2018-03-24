/*
 * XML.cpp
 *
 *  Created on: 14.03.2018
 *      Author: christoph
 */

#include "XML.hpp"
#include <Math/Math.hpp>
#include <cstddef>

XMLNode *insertNodeCopy(XMLNode *node, XMLNode *parentAim)
{
	XMLNode *clone = static_cast<XMLNode*>(node->ShallowClone(parentAim->GetDocument()));
	parentAim->InsertEndChild(clone);
	for (XMLNode *child = node->FirstChild(); child; child = child->NextSibling()) {
		insertNodeCopy(child, clone);
	}
	return clone;
}

XMLElement *insertElementCopy(XMLElement *element, XMLElement *parentAim)
{
	return (XMLElement*)insertNodeCopy(element, parentAim);
}

XMLElement *getChildWithID(XMLElement *parent, const char *id)
{
	for (XMLElement *child = parent->FirstChildElement(); child; child = child->NextSibling()->ToElement()) {
		if (child->Attribute("id")) {
			return child;
		}
		if (child->NextSibling() == 0)
			break;
	}
	return NULL;
}

XMLElement *firstChildWithAttribute(XMLElement *parent, const char *attributeName, const char *attributeValue)
{
	for(XMLElement *child = parent->FirstChildElement(); child; child = child->NextSibling()->ToElement()) {
		if (child->Attribute(attributeName) && strcmp(child->Attribute(attributeName), attributeValue) == 0) {
			return child;
		}
		if (child->NextSibling() == 0)
			break;
	}
	return NULL;
}


void pushAttributeNotEqual(XMLPrinter *printer, const char *key, const string &value, const string &standard)
{
	if (value != standard) {
		printer->PushAttribute(key, value.c_str());
	}
}

void pushAttributeNotEqual(XMLPrinter *printer, const char *key, const float &value, const float &standard)
{
	// Special case for floats: test if the values equal approximately
	if (!Math::floatEquals(value, standard)) {
		printer->PushAttribute(key, value);
	}
}
