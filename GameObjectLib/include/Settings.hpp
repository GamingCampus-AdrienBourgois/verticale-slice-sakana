#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Window.hpp"
#include "MenuObject.hpp"
#include "Slider.hpp"
#include "Music.hpp"

class Settings : public MenuObject {
public:
    Settings(Window_s& window, Music& music);
    ~Settings() = default;

    void valueChanger(Window_s& window, Music& music);
    void load(Window_s& window);
    void drawSliders(Window_s& window);
    void handleMouseDrag(const sf::Event& event, Window_s& window);
    void handleButtonClick(const sf::Event& event, Window_s& window, Music& music);

private:
    sf::Vector2u _resolution;
    bool resolutionChanged;

    bool isVsync;
    bool vsyncChanged;

    Slider volumeSlider;
    Slider fpsSlider;
};
