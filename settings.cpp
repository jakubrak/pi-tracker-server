#include "settings.h"

Settings::Settings() {

}

int Settings::getVideoPort() const {
    return videoPort;
}

void Settings::setVideoPort(int value) {
    videoPort = value;
}

int Settings::getMetadataPort() const {
    return metadataPort;
}

void Settings::setMetadataPort(int value) {
    metadataPort = value;
}

int Settings::getTcpPort() const {
    return tcpPort;
}

void Settings::setTcpPort(int value) {
    tcpPort = value;
}

std::string Settings::getVideoSource() const {
    return videoSource;
}

void Settings::setVideoSource(const std::string &value)
{
    videoSource = value;
}

int Settings::getFrameWidth() const {
    return frameWidth;
}

void Settings::setFrameWidth(int value) {
    frameWidth = value;
}

int Settings::getFrameHeight() const {
    return frameHeight;
}

void Settings::setFrameHeight(int value) {
    frameHeight = value;
}

double Settings::getFrameRate() const {
    return frameRate;
}

void Settings::setFrameRate(double value) {
    frameRate = value;
}
