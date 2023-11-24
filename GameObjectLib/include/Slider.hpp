#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Window.hpp"
#include "MenuObject.hpp"

class Slider {
public:
    Slider(float x, float y, float width, float min, float max, float currentValue);

    void draw(Window_s& window);
    bool handleMouseDrag(const sf::Event& event, sf::RenderWindow& window);
    float getValue() const;
    void setValue(float _value);
    const sf::RectangleShape getBar() const;
    const bool getisDragging() const;
private:
    sf::RectangleShape bar; // the bar of the slider
    sf::RectangleShape handle; // the draggable handle of the slider
    sf::Text valueText; // text to display the current value
    sf::Font font; // font for the text

    float minValue;
    float maxValue;
    float value;
    bool isDragging = false;
};
