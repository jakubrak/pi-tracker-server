#ifndef MESSAGEPARSER_H
#define MESSAGEPARSER_H

#include <memory>
#include <stack>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "imessagehandler.h"
#include "imessagelistener.h"

class MessageParser : public IMessageListener {
public:
    virtual ~MessageParser() {}

    void received(std::istream &is) override;

    void parse(std::istream &is);

    void addMessageHandler(std::shared_ptr<IMessageHandler> messageHandler);

private:
    void parse(const boost::property_tree::ptree &pt);

    template<typename T>
    void notifyHandlers(const T& message) {
        for (auto &h : messageHandlers) {
            h->handle(message);
        }
    }

    std::stringstream buffer;
    std::stack<char> stack;
    std::vector<std::shared_ptr<IMessageHandler>> messageHandlers;
};

#endif // MESSAGEPARSER_H
