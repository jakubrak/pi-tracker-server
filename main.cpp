#include <iostream>
#include <memory>

#include "messagehandler.h"
#include "messageparser.h"
#include "tcpserver.h"

int main(int argc, char** argv) {
    try {
        auto server = std::make_shared<TcpServer>(5002);
        auto messageParser = std::make_shared<MessageParser>();
        auto messageHandler = std::make_shared<MessageHandler>();

        server->addMessageListener(messageParser);
        messageParser->addMessageHandler(messageHandler);
        messageHandler->addMessageWriter(server);

        server->run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

	std::cout << "Exit" << std::endl;
	return 0;
}

