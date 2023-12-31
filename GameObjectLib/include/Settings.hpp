#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <memory>

#include "Window.hpp"
#include "MenuObject.hpp"
#include "Slider.hpp"
#include "Music.hpp"
#include "GameStatistics.hpp"

class Settings : public MenuObject {
public:
    Settings(Window_s& window, Music& music);
    ~Settings() = default;

    void textureSetters(Window_s& window);
    void load(Window_s& window);
    void drawSliders(Window_s& window);
    void handleMouseDrag(const sf::Event& event, Window_s& window);
    void handleButtonClick(const sf::Event& event, Window_s& window, Music& music);

    // Value operation (saving data, loading data from file and applying data)
    void valueChanger(Window_s& window, Music& music);
    void valueSetter(Window_s& window, Music& music);
    const std::string getSettingsFile() const;

    // Surcharge de reload
    void reloding(Window_s& window);

private:
    sf::Vector2u _resolution;
    bool resolutionChanged;

    bool isMax;
    bool isMin;
    bool pauseChanged;
    bool paused; // Need the condition for load

    bool Vsync; // Need the condition for load
    bool vsyncChanged;

    std::unique_ptr<Slider> volumeSlider;
    std::unique_ptr<Slider> fpsSlider;

    std::string settingsFile;
};