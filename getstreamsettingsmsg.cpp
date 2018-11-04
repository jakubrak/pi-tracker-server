#include "imessagehandler.h"
#include "imessageparser.h"

#include "getstreamsettingsmsg.h"

std::unique_ptr<IMessage> GetStreamSettingsMsg::handle(IMessageHandler& messageHandler) {
    return messageHandler.handle(*this);
}

std::string GetStreamSettingsMsg::unparse(IMessageParser& messageParser) {
    return messageParser.unparse(*this);
}
