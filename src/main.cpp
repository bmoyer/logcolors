#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

struct Color {
    int r;
    int g;
    int b;

    Color(int r, int g, int b) {
        this->r = r;
        this->g = g;
        this->b = g;
    }
};

std::ostream& operator<<(std::ostream& os, const Color& color) {
    return os << "[" << color.r << ", " << color.g << ", " << color.b << "]";
}

std::map<std::string, Color> getColorMap(std::string configFilePath) {
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

// TODO: prevent or handle multiple matches in 1 log line (either add both and print a warning, or disallow)
std::vector<Color> createColorSequenceFromLog(std::map<std::string, Color> regexToColor, std::string logFilePath) {
    std::vector<Color> colorSequence;

    std::ifstream logFile(logFilePath);
    std::string line;
    int lineNum = 1;
    while(std::getline(logFile, line)) {
        int matchesForLine = 0;
        for(auto it = regexToColor.begin(); it != regexToColor.end(); ++it) {
            std::regex logPattern(it->first);
            std::smatch match;
            if(std::regex_match(line, match, logPattern)) {
                std::cout << "Line \"" << line << "\" matched expression:" << it->first << std::endl;
                matchesForLine++;
            }
        }

        if(matchesForLine > 1) {
            std::cout << "Warning: line " << lineNum << " matched " << matchesForLine << " expressions\n";
        }
        lineNum++;
    }

    return colorSequence;
}

int main(int argc, char* argv[]) {
    std::string configFilePath = argv[1];
    std::string logFilePath = argv[2];

    std::map<std::string, Color> regexToColor = getColorMap(configFilePath);
    std::vector<Color> colorSequence = createColorSequenceFromLog(regexToColor, logFilePath);
    // image width, bar width, bar height, max image height
    const int IMAGE_WIDTH = 1000;
    const int MAX_IMAGE_HEIGHT = 1000;
    const int BAR_WIDTH = 10;
    const int BAR_HEIGHT = 100;

    return 0;
}
