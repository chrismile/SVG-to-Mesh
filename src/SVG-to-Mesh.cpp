//============================================================================
// Name        : SVG-to-Mesh.cpp
// Author      : Christoph Neuhauser
// Version     : 0.1
// Copyright   : GNU GPLv3 (for more details see LICENSE file)
//============================================================================

#include <iostream>
#include "Utils/Settings.hpp"

using namespace std;

void outputHelp() {
	cout << "The program converts a SVG file to a mesh in XML format usable for game engines." << endl;
	cout << "You need to pass the following arguments to the application:" << endl;
	cout << "  -input=\"<filename-svg>\"         The filename of the SVG file (normally *.svg)." << endl;
	cout << "  -output=\"<filename-mesh>\"       The filename of the output mesh file (normally *.xml)." << endl;
	cout << endl << "Opional arguments:" << endl;
	cout << "  -svgID=\"<element-id>\"           Pass an element ID of an SVG path or group if only it shall be converted." << endl;
	cout << "  -centered=<true/false>          Whether the origin of the output mesh should be the center of the bounding box." << endl;
	cout << "  -centered_viewbox=<true/false>  Whether the origin of the output mesh should be the center of the SVG view box." << endl;
	cout << "                                  Note: \'viewbox\' property needs to be set in SVG root element." << endl;
	cout << "Note: 'centered' and 'centered_viewbox' are mutually exclusive!" << endl;
}

// TODO: New version
bool executeCommand(string command) {
	// Fill the command arguments
	map<string, string> commands;
	string key = "", value = "";
	bool isInQuotationMarks = false;
	bool isInKey = true; // Scheme "-key=value"
	bool minusReached = false;
	for (auto it = command.begin(); it != command.end(); ++it) {
		if (isInKey) {
			if (*it == '=') {
				isInKey = false;
				minusReached = false;
			} else if (*it == ' ') {
				commands.insert(make_pair(key, ""));
				key = "";
			} else if (minusReached) {
				key += *it;
			}

			if (*it == '-') {
				minusReached = true;
			}
		} else {
			if (*it == '\"') {
				isInQuotationMarks = !isInQuotationMarks;
			} else if (*it == ' ') {
				if (!isInQuotationMarks) {
					isInKey = true;
					commands.insert(make_pair(key, value));
					key = "";
					value = "";
				}
			} else {
				value += *it;
			}
		}
	}

	if (key.length() > 0) {
		commands.insert(make_pair(key, value));
	}

	Settings::get()->clear();
	for (auto it = commands.begin(); it != commands.end(); ++it) {
		cout << "Key: \"" << it->first << "\", Value: \"" << it->second << "\"." << endl;
		Settings::get()->addKeyValue(it->first.c_str(), it->second.c_str());
	}

	if (command == "stop" || command == "end" || command == "exit"
			|| command == "quit" || command.length() == 0) {
		return false;
	} else if (command == "-help") {
		outputHelp();
	} else {
		//svgToMesh();
	}
	return true;
}

int main(int argc, char *argv[]) {
	if (argc > 1) {
		// Mode #1: Calling the program with command line arguments
		string arguments = "";
		for (int i = 1; i < argc; ++i) {
			arguments += argv[i];
			if (i != argc - 1) {
				arguments += " ";
			}
		}
		executeCommand(arguments);
	} else {
		// Mode #2: Interactive mode - passing commands using the command line (mainly for testing)
		bool running = true;
		do {
			cout << "Please enter a command (-help for help):" << endl;
			string command;
			getline(cin, command);
			running = executeCommand(command);
		} while (running);
	}

	cout << "Program quits now." << endl;
	return 0;
}
