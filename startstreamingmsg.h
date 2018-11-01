#ifndef STARTSTREAMINGMSG_H
#define STARTSTREAMINGMSG_H

#include <string>

class StartStreamingMsg {
public:
    StartStreamingMsg(const std::string& remoteAddress);

    const std::string getRemoteAddress() const {
        return remoteAddress;
    }

private:
    std::string remoteAddress;
};

#endif // STARTSTREAMINGMSG_H
