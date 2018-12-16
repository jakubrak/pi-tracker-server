#include <iostream>

#include <boost/property_tree/json_parser.hpp>

#include "irequestmessage.h"
#include "startstreamingrequest.h"
#include "streamsettingsrequest.h"
#include "streamsettingsresponse.h"

#include "messageparser.h"

std::vector<std::unique_ptr<IRequestMessage>> MessageParser::parse(std::istream& is) {
    std::vector<std::unique_ptr<IRequestMessage>> messageQueue;
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

std::unique_ptr<IRequestMessage> MessageParser::parse(const boost::property_tree::ptree& pt) {
    std::string messageId = pt.get<std::string>("msgid");
    if (messageId == "GET_STREAM_SETTINGS") {
        return std::make_unique<StreamSettingsRequest>();
    } else if (messageId == "START_STREAMING") {
        return std::make_unique<StartStreamingRequest>("192.168.0.158");
    }
    std::cerr << "Received unrecognized message: " << messageId << std::endl;
    return nullptr;
}

std::string MessageParser::unparse(const StreamSettingsResponse& message) {
    boost::property_tree::ptree pt;
    pt.put("msgid", "STREAM_SETTINGS");
    pt.put("port.video", message.getVideoPort());
    pt.put("port.metadata", message.getMetadataPort());
    pt.put("frame.width", message.getFrameWidth());
    pt.put("frame.height", message.getFrameHeight());
    pt.put("frame.rate", message.getFrameRate());
    std::stringstream output;
    boost::property_tree::json_parser::write_json(output, pt);
    return output.str();
}
