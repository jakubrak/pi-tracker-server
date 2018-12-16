#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H 

#include <memory>
#include <vector>

#include "imessagehandler.h"

class IResponseMessage;
class Settings;
class Pipeline;

class MessageHandler : public IMessageHandler {
public:
    MessageHandler(Settings& settings, Pipeline &pipeline);

    ~MessageHandler() override = default;

    std::unique_ptr<IResponseMessage> handle(const StreamSettingsRequest& getStreamSettingsMsg) override;

    std::unique_ptr<IResponseMessage> handle(const StartStreamingRequest& startStreamingRequest) override;

private:
    Settings& settings;
    Pipeline& pipeline;
};

#endif // MESSAGEHANDLER_H
