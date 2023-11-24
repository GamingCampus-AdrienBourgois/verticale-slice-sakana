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
    void loadSettings(Window_s& window);

    void drawSliders(Window_s& window);
    void handleMouseDrag(const sf::Event& event, Window_s& window);


private:
    Slider volumeSlider;
    Slider fpsSlider;
};
