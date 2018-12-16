#include <iostream>
#include <memory>

#include <gst/gst.h>

#include "messagehandler.h"
#include "messageparser.h"
#include "settings.h"
#include "tcpserver.h"
#include "pipeline.h"

int main(int argc, char** argv) {
    gst_init (&argc, &argv);
    try {
        while (true) {
            MessageParser messageParser;
            Settings settings;
            Pipeline pipeline;
            MessageHandler messageHandler(settings, pipeline);
            TcpServer server(5022, messageParser, messageHandler);
            server.run();
        }

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

	std::cout << "Exit" << std::endl;
	return 0;
}

