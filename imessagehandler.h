#ifndef IMESSAGEHANDLER_H
#define IMESSAGEHANDLER_H

class StartStreamingMsg;
class GetStreamSettingsMsg;

class IMessageHandler {
public:
    virtual void handle(const GetStreamSettingsMsg &getStreamSettingsMsg) = 0;

    virtual void handle(const StartStreamingMsg &startStreamingMsg) = 0;
};

#endif // IMESSAGEHANDLER_H
