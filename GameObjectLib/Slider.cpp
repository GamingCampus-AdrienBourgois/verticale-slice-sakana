#include "Slider.hpp"

Slider::Slider(float x, float y, float width, float min, float max, float currentValue)
    : minValue(min), maxValue(max), value(currentValue) {
    // Bar setup
    bar.setPosition(x, y);
    bar.setSize(sf::Vector2f(width, 10));
    bar.setFillColor(sf::Color(255, 255, 255));

    // Handle setup
    handle.setSize(sf::Vector2f(10, 20));
    handle.setFillColor(sf::Color(255, 0, 0));
    handle.setPosition(x + (currentValue - min) / (max - min) * width, y - 5);

    // Value text setup
    if (!font.loadFromFile("asset/font/Beyonders.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    valueText.setFont(font);
    valueText.setString(std::to_string(static_cast<int>(currentValue)));
    valueText.setCharacterSize(15);
    valueText.setFillColor(sf::Color(255, 255, 255));
    valueText.setPosition(x + width + 10, y);
}

void Slider::draw(Window_s& window) {
    window.addToRenderLayer(3, bar);
    window.addToRenderLayer(4, handle);
    window.addToRenderLayer(5, valueText);
}

bool Slider::handleMouseDrag(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (handle.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isDragging = true;
                return true;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            isDragging = false;
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        if (isDragging) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            float newPos = mousePos.x - bar.getPosition().x;
            newPos = std::max(newPos, 0.f);
            newPos = std::min(newPos, bar.getSize().x);
            handle.setPosition(bar.getPosition().x + newPos, handle.getPosition().y);

            // Update value
            value = minValue + (newPos / bar.getSize().x) * (maxValue - minValue);
            valueText.setString(std::to_string(static_cast<int>(value)));

            return true;
        }
    }
    return false;
}

float Slider::getValue() const {
    return value;
}
const sf::RectangleShape Slider::getBar() const {
    return bar;
}