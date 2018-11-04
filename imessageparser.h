#ifndef IMESSAGEPARSER_H
#define IMESSAGEPARSER_H

#include <memory>
#include <vector>

class IRequestMessage;
class StreamSettingsResponse;

class IMessageParser {
public:
    virtual ~IMessageParser() = default;

    virtual std::vector<std::unique_ptr<IRequestMessage>> parse(std::istream& is) = 0;

    virtual std::string unparse(const StreamSettingsResponse& message) = 0;
};

#endif // IMESSAGEPARSER_H
