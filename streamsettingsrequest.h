#ifndef GETSTREAMSETTINGSMSG_H
#define GETSTREAMSETTINGSMSG_H

#include "irequestmessage.h"

class IMessageHandler;

class StreamSettingsRequest : public IRequestMessage {
public:
    StreamSettingsRequest() = default;

    ~StreamSettingsRequest() override = default;

    std::unique_ptr<IResponseMessage> handle(IMessageHandler& messageHandler) override;
};

#endif // GETSTREAMSETTINGSMSG_H
