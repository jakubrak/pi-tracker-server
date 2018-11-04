#include "imessagehandler.h"
#include "iresponsemessage.h"

#include "streamsettingsrequest.h"

std::unique_ptr<IResponseMessage> StreamSettingsRequest::handle(IMessageHandler& messageHandler) {
    return messageHandler.handle(*this);
}

