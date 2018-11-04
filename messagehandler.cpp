#include <iostream>

#include "getstreamsettingsmsg.h"
#include "startstreamingmsg.h"

#include "messagehandler.h"

MessageHandler::MessageHandler(Settings& settings) : settings{settings} {

}

std::unique_ptr<IMessage> MessageHandler::handle(const GetStreamSettingsMsg& getStreamSettingsMsg) {
    std::cout << "GetStreamSettingsMsg" << std::endl;
    return nullptr;
}

std::unique_ptr<IMessage> MessageHandler::handle(const StartStreamingMsg& startStreamingMsg) {
    std::cout << "StartStreamingMsg" << std::endl;
    return nullptr;
}


