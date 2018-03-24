/*
 * Settings.hpp
 *
 *  Created on: 14.03.2018
 *      Author: christoph
 */

#ifndef UTILS_SETTINGS_HPP_
#define UTILS_SETTINGS_HPP_

#include <map>
#include <string>
#include <Graphics/Color.hpp>
#include <SVG/Parse/ParseColor.hpp>
#include <Utils/Convert.hpp>
#include <Utils/Singleton.hpp>

/**
 * Command line arguments passed to the application are stored in a singleton instance of this class.
 * Use addKeyValue to add a new settings value as a key-value pair.
 * Use getValue<Type>(...) to get the setting value for a certain key.
 */
class Settings : public Singleton<Settings>
{
public:
	// Getters for different kinds of data types
	inline std::string getValue(const std::string &key) { auto it = settings.find(key); return it == settings.end() ? "" : it->second; }
	inline int getIntValue(const std::string &key) { return Convert::fromString<int>(getValue(key)); }
	inline float getFloatValue(const std::string &key) { return Convert::fromString<float>(getValue(key)); }
	/// Special case bool: Only returns false if the saved value is "false", "0" or not set (otherwise true).
	inline bool getBoolValue(const std::string &key) { std::string val = getValue(key); if (val == "false" || val == "0") return false; return val.length() > 0; }
	/// Special case color: Interpret as CSS3 color
	inline Color getColorValue(const std::string &key) { std::string val = getValue(key); return parseCSS3ColorString(val); }

	/// Add key/value pair
	inline void addKeyValue(const char *key, const char *value) { settings[key] = value; }
	/// Delete all settings stored so far
	inline void clear() { settings.clear(); }

private:
	std::map<std::string, std::string> settings;
};

#endif /* UTILS_SETTINGS_HPP_ */
