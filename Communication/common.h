#ifndef COMMON_H
#define COMMON_H

#ifdef WIN32

#include <Windows.h>
#include <tchar.h>

#else

#include <unistd.h>

#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <ctime>
#include <mutex>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

typedef struct Mask {
	cv::Mat frame;
	cv::Scalar lower;
	cv::Scalar upper;
} Mask;

class common {
public:
	static bool is_running;
	static std::vector<std::vector<char>> frames;

	static int ball_x;
	static int ball_y;
	static int ball_radius_int;
	
	static Mask *mask;
	static cv::Point2f ball_center;
	static float ball_radius;
	static std::mutex wait_mutex;
	static std::string esp_ip;
};

#endif // COMMON_H
