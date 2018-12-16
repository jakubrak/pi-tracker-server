#include "imessageparser.h"

#include "streamsettingsresponse.h"

StreamSettingsResponse::StreamSettingsResponse(const int videoPort, const int metadataPort,
    const int frameWidth,
    const int frameHeight,
    const double frameRate)
    : videoPort{videoPort},
      metadataPort{metadataPort},
      frameWidth{frameWidth},
      frameHeight{frameHeight},
      frameRate{frameRate} {

}

int StreamSettingsResponse::getVideoPort() const {
    return videoPort;
}

int StreamSettingsResponse::getMetadataPort() const {
    return metadataPort;
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

