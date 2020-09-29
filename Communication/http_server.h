#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "common.h"
#include "External/HTTPRequest.hpp"

#include <cpprest/http_listener.h>
#include <cpprest/filestream.h>

using namespace web::http;
using namespace web::http::experimental::listener;

std::string get_host_name();
std::string get_host_ip();
void serve_clients();
void handle_get_frame(http_request request);
void handle_get_ball_coordinates(http_request request);
void handle_get_ball_simulation(http_request request);
void handle_send_bounce(http_request request);
void handle_send_circle(http_request request);
void handle_send_rectangle(http_request request);

#endif // HTTP_SERVER_H