#ifndef STREAMSETTINGSRESPONSE_H
#define STREAMSETTINGSRESPONSE_H

#include "iresponsemessage.h"

class StreamSettingsResponse : public IResponseMessage {
public:
    StreamSettingsResponse(const int videoPort,
       const int metadataPort,
       const int frameWidth,
       const int frameHeight,
       const double frameRate);

    int getVideoPort() const;

    int getMetadataPort() const;

    int getFrameWidth() const;

    int getFrameHeight() const;

    double getFrameRate() const;

    std::string unparse(IMessageParser& messageParser) override;

private:
    int videoPort;
    int metadataPort;
    int frameWidth;
    int frameHeight;
    double frameRate;
};

#endif // STREAMSETTINGSRESPONSE_H
