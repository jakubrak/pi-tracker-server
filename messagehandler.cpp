#include <iostream>

#include "iresponsemessage.h"
#include "settings.h"
#include "streamsettingsresponse.h"

#include "messagehandler.h"

MessageHandler::MessageHandler(Settings& settings) : settings{settings} {

}

std::unique_ptr<IResponseMessage> MessageHandler::handle(const StreamSettingsRequest& streamSettingsRequest) {
    std::cout << "GetStreamSettingsMsg" << std::endl;
    return std::make_unique<StreamSettingsResponse>(settings.getVideoPort(),
                                                    settings.getMetadataPort(),
                                                    settings.getFrameWidth(),
                                                    settings.getFrameHeight(),
                                                    settings.getFrameRate());
}

std::unique_ptr<IResponseMessage> MessageHandler::handle(const StartStreamingRequest& startStreamingRequest) {
    std::cout << "StartStreamingMsg" << std::endl;
    return nullptr;
}


