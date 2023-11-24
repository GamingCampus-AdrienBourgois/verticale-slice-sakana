#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Window.hpp"

class Slider {
public:
    Slider(float x, float y, float width, float min, float max, float currentValue);

    void draw(Window_s& window);
    bool handleMouseDrag(const sf::Event& event, sf::RenderWindow& window);
    float getValue() const;
    const sf::RectangleShape getBar() const;
    const bool getisDragging() const;
private:
    sf::RectangleShape bar; // The bar of the slider
    sf::RectangleShape handle; // The draggable handle of the slider
    sf::Text valueText; // Text to display the current value
    sf::Font font; // Font for the text
    float minValue; // Minimum value of the slider
    float maxValue; // Maximum value of the slider
    float value; // Current value of the slider
    bool isDragging = false; // Is the user currently dragging the slider
};
