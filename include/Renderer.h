#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "SharedDataTypes.h"

namespace Renderer {
    cv::Mat Render(const std::vector<Color>& colorSequence, int imageWidth, int maxImageHeight, int barWidth, int barHeight);
}