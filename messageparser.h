#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <stack>

#include <boost/property_tree/ptree.hpp>

#include "imessageparser.h"

class MessageParser : public IMessageParser {
public:
    ~MessageParser() override = default;

    std::vector<std::unique_ptr<IMessage>> parse(std::istream& is) override;

    std::string unparse(const GetStreamSettingsMsg& message) override;

    std::string unparse(const StartStreamingMsg& message) override;

private:
    std::unique_ptr<IMessage> parse(const boost::property_tree::ptree& pt);

    std::stringstream buffer;
    std::stack<char> stack;
};

#endif // MESSAGEPARSER_H
