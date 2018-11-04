#include <boost/property_tree/json_parser.hpp>

#include "getstreamsettingsmsg.h"
#include "imessage.h"
#include "startstreamingmsg.h"

#include "messageparser.h"

std::vector<std::unique_ptr<IMessage>> MessageParser::parse(std::istream& is) {
    std::vector<std::unique_ptr<IMessage>> messageQueue;
    char c;
    while(is.get(c)) {
        buffer << c;
        if (c == '{') {
            stack.push(c);
        } else if (c == '}') {
            stack.pop();
            if (stack.empty()) {
                // got complete json document
                boost::property_tree::ptree pt;
                boost::property_tree::json_parser::read_json(buffer, pt);
                auto message = parse(pt);
                if (message != nullptr) {
                    messageQueue.push_back(std::move(message));
                }
            }
        }
    }
    return messageQueue;
}

std::unique_ptr<IMessage> MessageParser::parse(const boost::property_tree::ptree& pt) {
    std::string messageId = pt.get<std::string>("msgid");
    if (messageId == "GET_STREAM_SETTINGS") {
        return std::make_unique<GetStreamSettingsMsg>();
    } else if (messageId == "START_STREAMING") {
        return std::make_unique<StartStreamingMsg>("192.168.0.158");
    }
    return nullptr;
}

std::string MessageParser::unparse(const GetStreamSettingsMsg& message) {

}

std::string MessageParser::unparse(const StartStreamingMsg& message) {

}
