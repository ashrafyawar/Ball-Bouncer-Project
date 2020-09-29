#include "image_processing.h"

const std::vector<cv::Point> max_contour(std::vector<std::vector<cv::Point>> contours) {
	std::vector<cv::Point> c;
	double area, max = -1;
	for(size_t i = 0; i < contours.size(); i++) {
		area = cv::contourArea(contours[i]);
		if(area > max) {
			max = area;
			c = contours[i];
		}
	}

	return c;
}

void find_ball_data() {
	cv::Mat src = cv::imdecode(common::frames.back(), cv::IMREAD_UNCHANGED);
	cv::Mat frame;
	cv::flip(src, frame, 1);

	cv::cvtColor(frame, common::mask->frame, cv::COLOR_BGR2HSV);
	if(!common::mask->lower.isReal() && !common::mask->upper.isReal()) {
		cv::inRange(common::mask->frame, common::mask->lower, common::mask->upper, common::mask->frame);
		cv::erode(common::mask->frame, common::mask->frame, cv::Mat(), cv::Point(-1,-1), 2);
		cv::dilate(common::mask->frame, common::mask->frame, cv::Mat(), cv::Point(-1,-1), 2);
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(common::mask->frame, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		if(contours.size() > 0) {
			cv::minEnclosingCircle(max_contour(contours), common::ball_center, common::ball_radius);
			float center_x = common::ball_center.x;
			float center_y = common::ball_center.y;
			float radi = common::ball_radius;
			std::cout << "Found at: " << center_x << ", " << center_y << ". Radius: " << radi << std::endl;

			float max_x = 300;
			float max_y = 200;

			center_x = center_x / max_x * 500.0f;
			center_y = center_y / max_y * 500.0f;

			common::ball_x = center_x;
			common::ball_y = center_y;

			common::ball_radius_int = radi;
		}
	}
}
