#include "websocket_client.h"

void on_websocket_message(wpp_client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    auto payload = msg->get_payload();

    std::vector<char> current_frame_buffer;

    for (int i = 0; i < payload.size(); i++) {
    	current_frame_buffer.push_back(payload[i]);
    }

    if (current_frame_buffer.size() < 1000) {
    	std::cerr << "Frame is not valid!" << std::endl;
    	return;
    }

    common::frames.push_back(current_frame_buffer);

    find_ball_data();

    if (common::frames.size() == 255) {
    	common::frames.erase(common::frames.begin());
    }
}

void listen_websocket(std::string addr) {
    wpp_client client;

    try {
        client.set_access_channels(websocketpp::log::alevel::all);
        client.clear_access_channels(websocketpp::log::alevel::frame_payload);

        client.init_asio();

        client.set_message_handler(bind(&on_websocket_message,&client,::_1,::_2));

        websocketpp::lib::error_code err_code;
        wpp_client::connection_ptr con = client.get_connection("ws://" + addr + ":82", err_code);

        if (err_code) {
            std::cout << "Could not create connection because: " << err_code.message() << std::endl;
            return;
        }

        client.connect(con);
        client.run();
    } 
    catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
}
