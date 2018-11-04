#ifndef IMESSAGEHANDLER_H
#define IMESSAGEHANDLER_H

#include <memory>

class IMessage;
class StartStreamingMsg;
class GetStreamSettingsMsg;

class IMessageHandler {
public:
    virtual ~IMessageHandler() = default;

    virtual std::unique_ptr<IMessage> handle(const GetStreamSettingsMsg& getStreamSettingsMsg) = 0;

    virtual std::unique_ptr<IMessage> handle(const StartStreamingMsg& startStreamingMsg) = 0;
};

#endif // IMESSAGEHANDLER_H
