#include "ConfigReader.h"
#include "SharedDataTypes.h"

#include <fstream>
#include <iostream>
#include <regex>

std::map<std::string, Color> ConfigReader::getColorMap(std::string configFilePath) {
    std::ifstream inputFile(configFilePath);
    std::map<std::string, Color> regexToColor;
    std::smatch match;

    std::regex lineRegex(R"((.*),(\d+),(\d+),(\d+))");

    std::string line;
    while(std::getline(inputFile, line)) {
        std::smatch match;

        if (std::regex_match(line, match, lineRegex)) {
            std::string regexStr = match[1].str();
            int r = std::stoi(match[2].str());
            int g = std::stoi(match[3].str());
            int b = std::stoi(match[4].str());
            
            Color color(r, g, b);
            regexToColor.emplace(regexStr, color);
            std::cout << "Regex \"" << regexStr << "\" mapped to " << color << std::endl;
        }
        else {
            throw std::runtime_error("Failed to parse config file, got: " + line);
        }
    }

    return regexToColor;
}