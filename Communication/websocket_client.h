#ifndef WEBSOCKET_CLIENT_H
#define WEBSOCKET_CLIENT_H

#include "common.h"
#include "../ImageProcessing/image_processing.h"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef websocketpp::client<websocketpp::config::asio_client> wpp_client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

void listen_websocket(std::string addr);
void on_websocket_message(wpp_client* c, websocketpp::connection_hdl hdl, message_ptr msg);

#endif // WEBSOCKET_CLIENT_H