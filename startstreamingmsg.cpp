#include "imessagehandler.h"
#include "imessageparser.h"

#include "startstreamingmsg.h"

StartStreamingMsg::StartStreamingMsg(const std::string& remoteAddress) :
    remoteAddress(remoteAddress) {
}

std::unique_ptr<IMessage> StartStreamingMsg::handle(IMessageHandler& messageHandler) {
    return messageHandler.handle(*this);
}

std::string StartStreamingMsg::unparse(IMessageParser& messageParser) {
    return messageParser.unparse(*this);
}
