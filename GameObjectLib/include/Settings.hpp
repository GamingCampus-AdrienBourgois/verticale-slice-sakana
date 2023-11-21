#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Window.hpp"
#include "MenuObject.hpp"

class Settings : public MenuObject {
public:
    Settings();
    ~Settings() = default;

    void setVolume(float volume);
    float getVolume() const;

    void setFpsLimit(unsigned int fps);
    unsigned int getFpsLimit() const;

 
    void setResolution(const sf::Vector2u& resolution);
    sf::Vector2u getResolution() const;



    void loadSettings(Window_s& window);

private:

    float _volume;
    unsigned int _fpsLimit;
    sf::Vector2u _resolution;
};
