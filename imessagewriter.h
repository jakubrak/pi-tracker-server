#ifndef IMESSAGEWRITER_H
#define IMESSAGEWRITER_H

#include <istream>

class IMessageWriter {
public:
    virtual void send(std::istream &is) = 0;
};

#endif // IMESSAGEWRITER_H
