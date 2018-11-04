#include "settings.h"

Settings::Settings() {

}

short Settings::getUdpPort() const {
    return udpPort;
}

void Settings::setUdpPort(short value) {
    udpPort = value;
}

short Settings::getTcpPort() const {
    return tcpPort;
}

void Settings::setTcpPort(short value) {
    tcpPort = value;
}

std::string Settings::getVideoSource() const {
    return videoSource;
}

void Settings::setVideoSource(const std::string &value)
{
    videoSource = value;
}

unsigned int Settings::getFrameWidth() const {
    return frameWidth;
}

void Settings::setFrameWidth(unsigned int value) {
    frameWidth = value;
}

unsigned int Settings::getFrameHeight() const {
    return frameHeight;
}

void Settings::setFrameHeight(unsigned int value) {
    frameHeight = value;
}

float Settings::getFrameRate() const {
    return frameRate;
}

void Settings::setFrameRate(float value) {
    frameRate = value;
}
