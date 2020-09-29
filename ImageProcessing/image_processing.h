#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "../Communication/common.h"

const std::vector<cv::Point> max_contour(std::vector<std::vector<cv::Point>> contours);
void find_ball_data();

#endif // IMAGE_PROCESSING_H