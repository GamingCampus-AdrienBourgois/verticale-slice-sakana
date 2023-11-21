#include "Settings.hpp"

Settings::Settings() : _volume(100.0f), _fpsLimit(60), _resolution(1920, 1080)//, _menu() 
{
}

void Settings::setVolume(float volume) {
    _volume = volume;
}

float Settings::getVolume() const {
    return _volume;
}

void Settings::setFpsLimit(unsigned int fps) {
    _fpsLimit = fps;
}

unsigned int Settings::getFpsLimit() const {
    return _fpsLimit;
}

void Settings::setResolution(const sf::Vector2u& resolution) {
    _resolution = resolution;
}

sf::Vector2u Settings::getResolution() const {
    return _resolution;
}
