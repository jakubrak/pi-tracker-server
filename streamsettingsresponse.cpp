#include "imessageparser.h"

#include "streamsettingsresponse.h"

StreamSettingsResponse::StreamSettingsResponse(const short port,
    const int frameWidth,
    const int frameHeight,
    const double frameRate)
    : port{port},
      frameWidth{frameWidth},
      frameHeight{frameHeight},
      frameRate{frameRate} {

}

short StreamSettingsResponse::getPort() const {
    return port;
}

int StreamSettingsResponse::getFrameWidth() const {
    return frameWidth;
}

int StreamSettingsResponse::getFrameHeight() const {
    return frameHeight;
}

double StreamSettingsResponse::getFrameRate() const {
    return frameRate;
}

std::string StreamSettingsResponse::unparse(IMessageParser& messageParser) {
    return messageParser.unparse(*this);
}

