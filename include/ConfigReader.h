#pragma once

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "SharedDataTypes.h"

namespace ConfigReader {
    std::map<std::string, Color> getColorMap(std::string configFilePath);
    std::vector<Color> createColorSequenceFromLog(std::map<std::string, Color> regexToColor, std::string logFilePath);
}