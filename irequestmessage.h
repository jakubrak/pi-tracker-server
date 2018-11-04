#ifndef IREQUESTMESSAGE_H
#define IREQUESTMESSAGE_H

#include <memory>

class IMessageHandler;
class IResponseMessage;

class IRequestMessage {
public:
    virtual ~IRequestMessage() = default;

    virtual std::unique_ptr<IResponseMessage> handle(IMessageHandler& messageHandler) = 0;
};

#endif // IREQUESTMESSAGE_H
