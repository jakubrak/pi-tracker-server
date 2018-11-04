#ifndef STREAMSETTINGSRESPONSE_H
#define STREAMSETTINGSRESPONSE_H

#include "iresponsemessage.h"

class StreamSettingsResponse : public IResponseMessage {
public:
    StreamSettingsResponse(const short port,
       const int frameWidth,
       const int frameHeight,
       const double frameRate);

    short getPort() const;

    int getFrameWidth() const;

    int getFrameHeight() const;

    double getFrameRate() const;

    std::string unparse(IMessageParser& messageParser) override;

private:
    short port;
    int frameWidth;
    int frameHeight;
    double frameRate;
};

#endif // STREAMSETTINGSRESPONSE_H
