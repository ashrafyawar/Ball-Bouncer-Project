#include "http_server.h"

/*** compiler dependency ***/
std::mutex common::wait_mutex;

std::string get_host_name() {
	const int buffer_length = 256;
    char name[buffer_length];

#ifdef WIN32
    TCHAR info_buffer[buffer_length];
    DWORD len = buffer_length;
    memset(Name, 0, buffer_length);
    if(GetComputerName(info_buffer, &buffer_length)) {
        for(int i = 0; i < buffer_length; i++) {
            name[i] = info_buffer[i];
        }
    }
    else {
        strcpy(name, "err");
    }
#else
    memset(name, 0, buffer_length);
    gethostname(name, buffer_length);
#endif

    return std::string(name);
}

std::string get_host_ip() {
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    sockaddr_in loopback;

    if (sock == -1) {
        std::cout << "Socket failed" << std::endl;
        return "err";
    }

    std::memset(&loopback, 0, sizeof(loopback));
    loopback.sin_family = AF_INET;
    loopback.sin_addr.s_addr = INADDR_LOOPBACK;
    loopback.sin_port = htons(9);

    if (connect(sock, reinterpret_cast<sockaddr*>(&loopback), sizeof(loopback)) == -1) {
        close(sock);
        std::cout << "Could not connect" << std::endl;
        return "err";
    }

    socklen_t addrlen = sizeof(loopback);
    if (getsockname(sock, reinterpret_cast<sockaddr*>(&loopback), &addrlen) == -1) {
        close(sock);
        std::cout << "GetSockName failed" << std::endl;
        return "err";
    }

    close(sock);

    char buf[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &loopback.sin_addr, buf, INET_ADDRSTRLEN) == 0x0) {
        std::cout << "inet_ntop failed" << std::endl;
        return "err";
    } else {
    	return std::string(buf);
    }
}

void locker(int __attribute__((unused)))
{
	common::wait_mutex.unlock();
}

void serve_clients() {
	signal(SIGINT, &locker);
	signal(SIGTERM, &locker);
	common::wait_mutex.lock();
    std::srand(std::time(nullptr));

	std::cout << "Setting endpoints..." << std::endl;

	std::string host_name = get_host_name();
	std::string host_ip = get_host_ip();

	if (host_ip == "err") {
		std::cout << "An error occured while obtaining IP address. Please restart the system..." << std::endl;
		return;
	}

	if (host_name == "err") {
		std::cout << "An error occured while obtaining hostname. Please restart the system..." << std::endl;
		return;
	}

	std::cout << "IP address: " << host_ip << std::endl;
	std::cout << "Hostname: " << host_name << std::endl;

	std::string frame_endpoint_addr = "http://" + host_ip + ":3000/frame";
	std::string ball_endpoint_addr = "http://" + host_ip + ":3000/ball";
	std::string simulation_endpoint_addr = "http://" + host_ip + ":3000/simulation";
	std::string bounce_endpoint_addr = "http://" + host_ip + ":3000/bounce";
	std::string circle_endpoint_addr = "http://" + host_ip + ":3000/circle";
	std::string rectangle_endpoint_addr = "http://" + host_ip + ":3000/rectangle";

	std::string frame_host_addr = "http://" + host_name + ":3000/frame";
	std::string ball_host_addr = "http://" + host_name + ":3000/ball";
	std::string simulation_host_addr = "http://" + host_name + ":3000/simulation";
	std::string bounce_host_addr = "http://" + host_name + ":3000/bounce";
	std::string circle_host_addr = "http://" + host_name + ":3000/circle";
	std::string rectangle_host_addr = "http://" + host_name + ":3000/rectangle";

	std::cout << "Frame endpoint address: " << frame_host_addr << std::endl;
	std::cout << "Ball endpoint address: " << ball_host_addr << std::endl;
	std::cout << "Simulation endpoint address: " << simulation_host_addr << std::endl;
	std::cout << "Bounce endpoint address: " << bounce_host_addr << std::endl;
	std::cout << "Circle endpoint address: " << circle_host_addr << std::endl;
	std::cout << "Rectangle endpoint address: " << rectangle_host_addr << std::endl;

	http_listener frame_listener(frame_endpoint_addr);
	http_listener ball_listener(ball_endpoint_addr);
	http_listener simulation_listener(simulation_endpoint_addr);
	http_listener bounce_listener(bounce_endpoint_addr);
	http_listener circle_listener(circle_endpoint_addr);
	http_listener rectangle_listener(rectangle_endpoint_addr);
	
	frame_listener.support(methods::GET, handle_get_frame);
	ball_listener.support(methods::GET, handle_get_ball_coordinates);
	simulation_listener.support(methods::GET, handle_get_ball_simulation);
	bounce_listener.support(methods::GET, handle_send_bounce);
	circle_listener.support(methods::GET, handle_send_circle);
	rectangle_listener.support(methods::GET, handle_send_rectangle);

	try {
		frame_listener.open()
		.then([&frame_listener](){
			std::cout << "Frame endpoint started listening!" << std::endl;
		}).wait();

		ball_listener.open()
		.then([&ball_listener](){
			std::cout << "Ball information endpoint started listening!" << std::endl;
		}).wait();

		simulation_listener.open()
		.then([&simulation_listener](){
			std::cout << "Simulation information endpoint started listening!" << std::endl;
		}).wait();	

		bounce_listener.open()
		.then([&bounce_listener](){
			std::cout << "Bounce endpoint started listening!" << std::endl;
		}).wait();

		circle_listener.open()
		.then([&circle_listener](){
			std::cout << "Circle endpoint started listening!" << std::endl;
		}).wait();		

		rectangle_listener.open()
		.then([&rectangle_listener](){
			std::cout << "Rectangle endpoint started listening!" << std::endl;
		}).wait();								
	
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	common::wait_mutex.lock();
}

void handle_get_frame(http_request request) {
	if (common::frames.size() > 1) {
    	auto instream = Concurrency::streams::bytestream::open_istream(common::frames.back());
    	http_response response(status_codes::OK);
    	response.set_body(instream, "image/jpeg");
		request.reply(response);
	}
	else {
    	http_response response(status_codes::NotFound);
		response.set_body("No valid frames in the buffer!", "text/plain");
		request.reply(response);
	}
}

void handle_get_ball_coordinates(http_request request) {
	std::string response_body = std::to_string(common::ball_x) + "," + std::to_string(common::ball_y) + "," + std::to_string(common::ball_radius_int);
	
    http_response response(status_codes::OK);
	response.set_body(response_body, "text/plain");
	
	std::cout << "Response:" << response_body << std::endl;

	request.reply(response);
}

void handle_get_ball_simulation(http_request request) {
	auto ball_x_str = std::to_string(common::ball_x);
	auto ball_y_str = std::to_string(common::ball_y);
	auto ball_height_str = std::to_string(common::ball_radius_int);

	// TODO: Calc this:
	std::string right_arm_dir_str = "0";
	std::string left_arm_dir_str = "0";
	std::string up_arm_dir_str = "0";
	std::string down_arm_dir_str = "0";

	std::string response_body = 
								ball_x_str + "," +
								ball_y_str + "," +
								ball_height_str + "," +
								right_arm_dir_str + "," +
								left_arm_dir_str + "," +
								up_arm_dir_str + "," +
								down_arm_dir_str;

    http_response response(status_codes::OK);
	response.set_body(response_body, "text/plain");

	std::cout << "Response:" << response_body << std::endl;

	request.reply(response);
}

void handle_send_bounce(http_request request) {
	try {
		std::cout << "Bounce req." << std::endl;
		http::Request request(common::esp_ip + "/bounce");
		request.send("GET");
	}
	catch (const std::exception& e) {
		std::cout << "Bounce request failed, error: " << e.what() << std::endl;
	}

	http_response response(status_codes::OK);
	response.set_body("OK.", "text/plain");
	request.reply(response);
}

void handle_send_circle(http_request request) {
	try {
		std::cout << "Circle req." << std::endl;
		http::Request request(common::esp_ip + "/draw_circle");
		request.send("GET");
	}
	catch (const std::exception& e) {
		std::cout << "Circle request failed, error: " << e.what() << std::endl;
	}

	http_response response(status_codes::OK);
	response.set_body("OK.", "text/plain");
	request.reply(response);	
}

void handle_send_rectangle(http_request request) {
	try {
		std::cout << "Rectangle req." << std::endl;
		http::Request request(common::esp_ip + "/draw_rectangle");
		request.send("GET");
	}
	catch (const std::exception& e) {
		std::cout << "Rectangle request failed, error: " << e.what() << std::endl;
	}

	http_response response(status_codes::OK);
	response.set_body("OK.", "text/plain");
	request.reply(response);	
}
