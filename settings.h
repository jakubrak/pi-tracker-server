#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

class Settings
{
public:
    Settings();

    int getVideoPort() const;
    void setVideoPort(int value);

    int getMetadataPort() const;
    void setMetadataPort(int value);

    int getTcpPort() const;
    void setTcpPort(int value);

    std::string getVideoSource() const;
    void setVideoSource(const std::string &value);

    int getFrameWidth() const;
    void setFrameWidth(int value);

    int getFrameHeight() const;
    void setFrameHeight(int value);

    double getFrameRate() const;
    void setFrameRate(double value);


private:
    int videoPort = 5000;
    int metadataPort = 5006;
    int tcpPort = 5022;
    std::string videoSource = "/dev/video0";
    int frameWidth = 1280;
    int frameHeight = 720;
    double frameRate = 30.0f;
};

#endif // SETTINGS_H
