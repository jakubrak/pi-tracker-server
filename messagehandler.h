#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H 

#include <memory>
#include <vector>

#include "imessagehandler.h"

class IMessageWriter;
class Settings;

class MessageHandler : public IMessageHandler {
public:
    MessageHandler(Settings& settings);

    ~MessageHandler() override = default;

    std::unique_ptr<IMessage> handle(const GetStreamSettingsMsg& getStreamSettingsMsg) override;

    std::unique_ptr<IMessage> handle(const StartStreamingMsg& startStreamingMsg) override;

private:
    Settings& settings;
};

#endif // MESSAGEHANDLER_H
