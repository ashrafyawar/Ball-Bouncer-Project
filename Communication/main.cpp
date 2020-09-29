// CSE396 - Group 1
// Server Project

#include "websocket_client.h"
#include "http_server.h"

bool common::is_running;
std::string common::esp_ip = "BouncerESP32.local";
std::vector<std::vector<char>> common::frames;

int common::ball_x;
int common::ball_y;
int common::ball_radius_int;

Mask * common::mask;
cv::Point2f common::ball_center;
float common::ball_radius;

int main(int argc, char const *argv[]) {
	common::is_running = true;
	common::mask = new Mask;
	common::mask->lower = cv::Scalar(0, 96, 105);
	common::mask->upper = cv::Scalar(21, 255, 255);

	std::thread server_thread(serve_clients);
	std::thread listen_thread(listen_websocket, common::esp_ip);
	
	server_thread.join();
	listen_thread.join();

	delete common::mask;

	return 0;
}
