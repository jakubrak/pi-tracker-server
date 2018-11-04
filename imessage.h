#ifndef IMESSAGE_H
#define IMESSAGE_H

#include <memory>

class IMessageHandler;
class IMessageParser;

class IMessage {
public:
    virtual ~IMessage() = default;

    virtual std::unique_ptr<IMessage> handle(IMessageHandler& messageHandler) = 0;

    virtual std::string unparse(IMessageParser& messageParser) = 0;
};

#endif // IMESSAGE_H
