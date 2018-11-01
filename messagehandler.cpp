#include <iostream>

#include "getstreamsettingsmsg.h"
#include "startstreamingmsg.h"

#include "messagehandler.h"

void MessageHandler::handle(const GetStreamSettingsMsg &getStreamSettingsMsg) {
    std::cout << "GetStreamSettingsMsg" << std::endl;
}

void MessageHandler::handle(const StartStreamingMsg &startStreamingMsg) {
    std::cout << "StartStreamingMsg" << std::endl;
}

void MessageHandler::addMessageWriter(std::shared_ptr<IMessageWriter> messageWriter) {
    messageWriters.push_back(messageWriter);
}
