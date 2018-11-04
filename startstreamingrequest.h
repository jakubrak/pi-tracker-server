#ifndef STARTSTREAMINGREQUEST_H
#define STARTSTREAMINGREQUEST_H

#include <string>

#include "irequestmessage.h"

class StartStreamingRequest : public IRequestMessage {
public:
    StartStreamingRequest(const std::string& remoteAddress);

    ~StartStreamingRequest() override = default;

    const std::string getRemoteAddress() const {
        return remoteAddress;
    }

    std::unique_ptr<IResponseMessage> handle(IMessageHandler& messageHandler) override;

private:
    std::string remoteAddress;
};

#endif // STARTSTREAMINGREQUEST_H
