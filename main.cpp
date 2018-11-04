#include <iostream>
#include <memory>

#include "messagehandler.h"
#include "messageparser.h"
#include "settings.h"
#include "tcpserver.h"

int main(int argc, char** argv) {
    try {
        MessageParser messageParser;
        Settings settings;
        MessageHandler messageHandler(settings);
        TcpServer server(5002, messageParser, messageHandler);
        server.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

	std::cout << "Exit" << std::endl;
	return 0;
}

