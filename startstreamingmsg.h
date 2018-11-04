#ifndef STARTSTREAMINGMSG_H
#define STARTSTREAMINGMSG_H

#include <string>

#include "imessage.h"

class StartStreamingMsg : public IMessage {
public:
    StartStreamingMsg(const std::string& remoteAddress);

    ~StartStreamingMsg() override = default;

    const std::string getRemoteAddress() const {
        return remoteAddress;
    }

    std::unique_ptr<IMessage> handle(IMessageHandler& messageHandler) override;

    std::string unparse(IMessageParser& messageParser) override;

private:
    std::string remoteAddress;
};

#endif // STARTSTREAMINGMSG_H
