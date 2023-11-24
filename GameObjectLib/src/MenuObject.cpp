#include "MenuObject.hpp"
#include <iostream>

void MenuObject::draw(Window_s& window) {
    for (unsigned int i = 0; i < buttonCount; i++) {
        window.addToRenderLayer(2, buttonTexts[i]); // Add text on buttons
        window.addToRenderLayer(1, mapButton[i]); // Add buttons
    }
    for (size_t i = 0; i < basicTexts.size(); i++) {
        window.addToRenderLayer(6, basicTexts[i]);
    }
}

void MenuObject::resetValues(Window_s& window) {
    buttonTexts.clear();
    mapButton.clear();
    buttonCount = 0;
    window.clearLayer(1);
    window.clearLayer(2);
    window.clearLayer(3);
    window.clearLayer(4);
    window.clearLayer(5);
    window.clearLayer(6);
    window.clearLayer(7);
    window.clearLayer(8);
    window.clearLayer(9);
    window.clearLayer(10);
}

sf::Text MenuObject::setTextOnButton(const std::string& text, sf::RectangleShape& button, unsigned int size) {
    sf::Color color(0, 255, 0);
    sf::Text buttonText(text, _fontButton, size); // Taille de texte 20
    buttonText.setFillColor(color);
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(button.getPosition());
    return buttonText;
}

void MenuObject::changeOnMouse(Window_s& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
    sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);

    for (unsigned int i = 0; i < buttonCount; i++) {
        if (mapButton[i].getGlobalBounds().contains(mousePosF)) {
            mapButton[i].setFillColor(sf::Color(0, 0, 255)); // Couleur de survol
        }
        else {
            mapButton[i].setFillColor(sf::Color(255, 0, 0)); // Couleur par défaut

        }
    }
}

sf::Text MenuObject::createText(const std::string& text, const sf::Vector2f& position, unsigned int size) {
    sf::Text textObject;
    textObject.setFont(_fontAny);
    textObject.setString(text);
    textObject.setCharacterSize(size);
    textObject.setFillColor(sf::Color(255, 255, 255));
    textObject.setPosition(position);

    sf::FloatRect bounds = textObject.getLocalBounds();
    textObject.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    return textObject;
}


const MenuObject::MenuStates MenuObject::getMenuState() const {
    return _MenuState;
}

void MenuObject::setMenuState(MenuStates MenuState) {
    _MenuState = MenuState;
}
