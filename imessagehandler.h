#ifndef IMESSAGEHANDLER_H
#define IMESSAGEHANDLER_H

#include <memory>

class IResponseMessage;
class StartStreamingRequest;
class StreamSettingsRequest;

class IMessageHandler {
public:
    virtual ~IMessageHandler() = default;

    virtual std::unique_ptr<IResponseMessage> handle(const StreamSettingsRequest& getStreamSettingsMsg) = 0;

    virtual std::unique_ptr<IResponseMessage> handle(const StartStreamingRequest& startStreamingMsg) = 0;
};

#endif // IMESSAGEHANDLER_H
