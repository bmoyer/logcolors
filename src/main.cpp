#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <regex>

#include "SharedDataTypes.h"
#include "ConfigReader.h"
#include "Renderer.h"

// TODO: multithread this, regex is a bottleneck
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
                //std::cout << "Line \"" << line << "\" matched expression:" << it->first << std::endl;
                colorSequence.push_back(it->second);
                matchesForLine++;
            }
        }

        if(matchesForLine > 1) {
            // Allow a new bar to be drawn for each regex matching this line and log a warning
            std::cout << "Warning: line " << lineNum << " matched " << matchesForLine << " expressions\n";
        }
        lineNum++;
    }

    return colorSequence;
}

int main(int argc, char* argv[]) {
    std::string configFilePath = argv[1];
    std::string logFilePath = argv[2];

    std::map<std::string, Color> regexToColor = ConfigReader::getColorMap(configFilePath);
    std::vector<Color> colorSequence = createColorSequenceFromLog(regexToColor, logFilePath);
    std::cout << "Rendering " << colorSequence.size() << " events" << std::endl;

    // image width, bar width, bar height, max image height
    const int IMAGE_WIDTH = 1000;
    const int MAX_IMAGE_HEIGHT = 1000;
    const int BAR_WIDTH = 20;
    const int BAR_HEIGHT = 100;

    // max number of samples that can be drawn is: (width / bar width) * (max height / bar height)
    cv::Mat img = Renderer::Render(colorSequence, IMAGE_WIDTH, MAX_IMAGE_HEIGHT, BAR_WIDTH, BAR_HEIGHT);
    cv::imwrite("test.png", img);

    return 0;
}
