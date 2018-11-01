#ifndef IMESSAGELISTENER_H
#define IMESSAGELISTENER_H

#include <istream>

class IMessageListener {
public:
    virtual void received(std::istream &is) = 0;
};

#endif // IMESSAGELISTENER_H
