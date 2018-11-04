#ifndef GETSTREAMSETTINGSMSG_H
#define GETSTREAMSETTINGSMSG_H

#include "imessage.h"

class IMessageHandler;

class GetStreamSettingsMsg : public IMessage {
public:
    GetStreamSettingsMsg() = default;

    ~GetStreamSettingsMsg() override = default;

    std::unique_ptr<IMessage> handle(IMessageHandler& messageHandler) override;

    std::string unparse(IMessageParser& messageParser) override;
};

#endif // GETSTREAMSETTINGSMSG_H
