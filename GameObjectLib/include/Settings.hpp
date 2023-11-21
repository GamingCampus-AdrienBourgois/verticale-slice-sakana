#pragma once
#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "Menu.hpp"

class Settings {
public:
    Settings();
    ~Settings() = default;

    void setVolume(float volume);
    float getVolume() const;

    void setFpsLimit(unsigned int fps);
    unsigned int getFpsLimit() const;

 
    void setResolution(const sf::Vector2u& resolution);
    sf::Vector2u getResolution() const;

    void loadSettings(Window_s &window) {

    }

private:
    //Menu _menu;

    float _volume;
    unsigned int _fpsLimit;
    sf::Vector2u _resolution;
};
