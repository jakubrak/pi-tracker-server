#include "imessagehandler.h"
#include "iresponsemessage.h"
#include "startstreamingrequest.h"

StartStreamingRequest::StartStreamingRequest(const std::string& remoteAddress) :
    remoteAddress(remoteAddress) {
}

std::unique_ptr<IResponseMessage> StartStreamingRequest::handle(IMessageHandler& messageHandler) {
    return messageHandler.handle(*this);
}
