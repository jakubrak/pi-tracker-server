#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H 

#include <memory>
#include <vector>

#include "imessagehandler.h"

class IMessageWriter;

class MessageHandler : public IMessageHandler {
public:
    virtual ~MessageHandler() {}

    void handle(const GetStreamSettingsMsg &getStreamSettingsMsg) override;

    void handle(const StartStreamingMsg &startStreamingMsg) override;


    void addMessageWriter(std::shared_ptr<IMessageWriter> messageWriter);

private:
    std::vector<std::shared_ptr<IMessageWriter>> messageWriters;
};

#endif // MESSAGEHANDLER_H
