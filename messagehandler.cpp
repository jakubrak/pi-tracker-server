#include <iostream>

#include "iresponsemessage.h"
#include "settings.h"
#include "streamsettingsresponse.h"
#include "pipeline.h"

#include "messagehandler.h"

MessageHandler::MessageHandler(Settings& settings) : settings{settings}, pipeline{nullptr} {

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
    pipeline = std::make_unique<Pipeline>();
    pipeline->play();
    return nullptr;
}


