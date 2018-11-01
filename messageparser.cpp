#include <boost/property_tree/json_parser.hpp>

#include "getstreamsettingsmsg.h"
#include "startstreamingmsg.h"

#include "messageparser.h"

void MessageParser::received(std::istream &is) {
    parse(is);
}

void MessageParser::parse(std::istream &is) {
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
                parse(pt);
            }
        }
    }
}

void MessageParser::addMessageHandler(std::shared_ptr<IMessageHandler> messageHandler) {
    messageHandlers.push_back(messageHandler);
}

void MessageParser::parse(const boost::property_tree::ptree &pt) {
    std::string messageId = pt.get<std::string>("msgid");
    if (messageId == "GET_STREAM_SETTINGS") {
        GetStreamSettingsMsg message;
        notifyHandlers(message);
    } else if (messageId == "START_STREAMING") {
        StartStreamingMsg message("192.168.0.158");
        notifyHandlers(message);
    }
}
