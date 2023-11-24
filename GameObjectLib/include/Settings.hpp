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

class Settings : public MenuObject {
public:
    Settings(Window_s& window, Music& music);
    ~Settings() = default;

    void load(Window_s& window);
    void drawSliders(Window_s& window);
    void handleMouseDrag(const sf::Event& event, Window_s& window);
    void handleButtonClick(const sf::Event& event, Window_s& window, Music& music);

    // Value operation (saving data, loading data from file and applying data)
    void valueChanger(Window_s& window, Music& music);
    void valueSetter(Window_s& window, Music& music);
    static std::string getParamFromString(std::string param, const std::string& file); // utilisable partout dans le code car la fonction est utile
    static void saveSettingsValue(const std::string& param, const std::string& file, const std::string& newValue); // utilisable partout dans le code car la fonction est utile
    const std::string getSettingsFile() const;

private:
    sf::Vector2u _resolution;
    bool resolutionChanged;

    bool isVsync;
    bool vsyncChanged;

    std::unique_ptr<Slider> volumeSlider;
    std::unique_ptr<Slider> fpsSlider;

    std::string settingsFile;
};