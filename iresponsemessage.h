#ifndef IRESPONSEMESSAGE_H
#define IRESPONSEMESSAGE_H

#include <memory>

class IMessageParser;

class IResponseMessage {
public:
    virtual ~IResponseMessage() = default;

    virtual std::string unparse(IMessageParser& messageParser) = 0;
};

#endif // IRESPONSEMESSAGE_H
