#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

class Settings
{
public:
    Settings();

    short getUdpPort() const;
    void setUdpPort(short value);

    short getTcpPort() const;
    void setTcpPort(short value);

    std::string getVideoSource() const;
    void setVideoSource(const std::string &value);

    unsigned int getFrameWidth() const;
    void setFrameWidth(unsigned int value);

    unsigned int getFrameHeight() const;
    void setFrameHeight(unsigned int value);

    float getFrameRate() const;
    void setFrameRate(float value);

private:
    short udpPort = 5001;
    short tcpPort = 5002;
    std::string videoSource = "/dev/video0";
    unsigned int frameWidth = 1280;
    unsigned int frameHeight = 720;
    float frameRate = 30.0f;
};

#endif // SETTINGS_H
