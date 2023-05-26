#include <opencv2/imgproc/imgproc.hpp>

#include "Renderer.h"

#include <cmath>
#include <iostream>

cv::Mat Renderer::Render(const std::vector<Color>& colorSequence, int imageWidth, int maxImageHeight, int barWidth, int barHeight) {

    const int INTERROW_SPACING = 10;
    const int INTRAROW_SPACING = 1;
    
    int barsPerRow = imageWidth / (barWidth + INTRAROW_SPACING);

    //int imageHeight = (colorSequence.size() / barsPerRow) * (barHeight + INTERROW_SPACING);
    //imageHeight = std::max(imageHeight, maxImageHeight);
    int rowHeight = (barHeight + INTERROW_SPACING);
    int rowsPerImage = std::min(static_cast<int>(std::floor(maxImageHeight / rowHeight)), static_cast<int>(std::ceil((float)colorSequence.size() / (float)barsPerRow)));
    std::cout << "rows per image: " << rowsPerImage << "\n";
    std::cout << barsPerRow << std::endl;
    std::cout << colorSequence.size() << " " << barsPerRow << std::endl;

    int imageHeight = rowsPerImage * rowHeight;
    cv::Mat output(imageHeight, imageWidth, CV_8UC3, cv::Scalar(0, 0, 0));
    std::cout << "Image dimensions: " << imageHeight << " " << imageWidth << std::endl;
    for(int i = 0; i < colorSequence.size(); i++) {
        int row = i / barsPerRow;
        int col = i % barsPerRow;

        //std::cout << "row, col" << row << ", " << col << std::endl;

        if (row > rowsPerImage)
            break;

        int xCoord = col * (barWidth + INTRAROW_SPACING);
        int yCoord = row * (barHeight + INTERROW_SPACING);

        //std::cout << "Drawing rect with origin " << yCoord << ", " << xCoord << "\n";
        //cv::rectangle(output, 
        cv::Rect rect(xCoord, yCoord, barWidth, barHeight);
        //cv::rectangle(output, rect, cv::Scalar(255, 255, 255));
        cv::rectangle(output, rect, cv::Scalar(colorSequence[i].b, colorSequence[i].g, colorSequence[i].r, 255), cv::FILLED);
        std::cout << "Using color " << colorSequence[i] << std::endl;
    }

    return output;
}