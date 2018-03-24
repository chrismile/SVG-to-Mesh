/*
 * XML.hpp
 *
 *  Created on: 14.03.2018
 *      Author: christoph
 */

#ifndef XML_XML_HPP_
#define XML_XML_HPP_

#include <string>
#include <cassert>
#include <functional>
#include <tinyxml2.h>

using namespace tinyxml2;
using namespace std;

/**
 * Copys and pastes "element" including all of its child elements to "parentAim" (deep copy).
 * @return: The copied element.
 */
XMLElement *insertElementCopy(XMLElement *element, XMLElement *parentAim);

/// Returns the first child element of parent with the matching attribute "id"
XMLElement *getChildWithID(XMLElement *parent, const char *id);

/// Returns the first child element of parent with the matching attribute "attributeName"
XMLElement *firstChildWithAttribute(XMLElement *parent, const char *attributeName, const char *attributeValue);

/**
 * Pushes the "key" with the desired value on the XMLPrinter stack if "value" doesn't equal "standard".
 * Example: pushAttributeNotEqual(printer, "damping", damping, 0.0f);
 */
template<class T>
void pushAttributeNotEqual(XMLPrinter *printer, const char *key, const T &value, const T &standard)
{
	if (value != standard) {
		printer->PushAttribute(key, value);
	}
}
void pushAttributeNotEqual(XMLPrinter *printer, const char *key, const string &value, const string &standard);
void pushAttributeNotEqual(XMLPrinter *printer, const char *key, const float &value, const float &standard);



// Classes for easily iterating over XMLElements

/**
 * An XMLItFilter object encapsulates a function lambda deciding whether an XMLElement
 * child object of an XML node should be processed or not.
 * Predefined filters are e.g. @XMLNameFilter, @XMLAttributeFilter, @XMLAttributePresenceFilter.
 * They can be used for the class @XMLIterator (see below).
 */
typedef std::function<bool(tinyxml2::XMLElement*)> XMLItFilterFunc;
struct XMLItFilter {
public:
	XMLItFilter(std::function<bool(tinyxml2::XMLElement*)> f) { filterFunc = f; }
	XMLItFilter() : XMLItFilter([](tinyxml2::XMLElement* e) { return true; }) {}
	bool operator()(tinyxml2::XMLElement* element) { return filterFunc(element); }

private:
	XMLItFilterFunc filterFunc;
};

// E.g.: Name equals X, Attribute Y equals X
inline XMLItFilter XMLNameFilter(const string& name) {
	return XMLItFilter([name](tinyxml2::XMLElement* e) -> bool { return name == e->Name(); });
}
inline XMLItFilter XMLAttributeFilter(const string& attrName, const string& attrVal) {
	return XMLItFilter([attrName,attrVal](tinyxml2::XMLElement* e) -> bool { return attrVal == e->Attribute(attrName.c_str()); });
}
inline XMLItFilter XMLAttributePresenceFilter(const string& attrName) {
	return XMLItFilter([attrName](tinyxml2::XMLElement* e) -> bool { return e->Attribute(attrName.c_str()) != NULL; });
}


/**
 * Ax XMLIterator can be used to iterate over all child elements of an XML element node.
 * Example:
 *    for (XMLIterator it(parent); it.isValid(); ++it) { it->... }
 * Optionally, you can pass an instance of an @XMLItFilter to the constructor, e.g. if
 * only certain nodes shall be processed.
 */
class XMLIterator : public iterator<std::input_iterator_tag, tinyxml2::XMLElement> {
private:
	tinyxml2::XMLElement *element;
	XMLItFilter filter;

public:
	XMLIterator(tinyxml2::XMLElement* e, XMLItFilter f) : filter(f) {
		element = e->FirstChildElement();
		if (element != NULL && !filter(element)) {
			operator++();
		}
	}
	XMLIterator(tinyxml2::XMLElement* e) : XMLIterator(e, XMLItFilter()) { }
	XMLIterator(const XMLIterator& otherIt) : XMLIterator(otherIt.element) {}

	XMLIterator& operator++() {
		do {
			tinyxml2::XMLNode* next = element->NextSibling();
			element = next ? next->ToElement() : NULL;
		} while (element != NULL && !filter(element));
		return *this;
	}
	bool operator==(const XMLIterator& rhs) { return element==rhs.element; }
	bool operator!=(const XMLIterator& rhs) { return element!=rhs.element; }
	tinyxml2::XMLElement* operator*() { assert(element); return element; }
	tinyxml2::XMLElement* operator->() { assert(element); return element; }
	bool isValid() { return element != NULL; }
};

#endif /* XML_XML_HPP_ */
