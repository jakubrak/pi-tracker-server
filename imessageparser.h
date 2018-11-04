#ifndef IMESSAGEPARSER_H
#define IMESSAGEPARSER_H

#include <memory>
#include <vector>

class IMessage;
class GetStreamSettingsMsg;
class StartStreamingMsg;

class IMessageParser {
public:
    virtual ~IMessageParser() = default;

    virtual std::vector<std::unique_ptr<IMessage>> parse(std::istream& is) = 0;

    virtual std::string unparse(const GetStreamSettingsMsg& message) = 0;

    virtual std::string unparse(const StartStreamingMsg& message) = 0;
};

#endif // IMESSAGEPARSER_H
