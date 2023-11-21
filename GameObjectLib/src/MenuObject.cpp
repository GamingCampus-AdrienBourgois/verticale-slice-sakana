#include "MenuObject.hpp"
#include <iostream>

void MenuObject::draw(Window_s& window) {
    for (unsigned int i = 0; i < buttonCount; i++) {
        window.addToRenderLayer(2, buttonTexts[i]); // Add text on buttons
        window.addToRenderLayer(1, mapButton[_MenuState][i]); // Add buttons
    }
}

void MenuObject::resetValues(Window_s& window) {
    buttonTexts.clear();
    for (auto& stateButtons : mapButton) {
        stateButtons.second.clear();
    }
    buttonCount = 0;
    window.clearLayer(1);
    window.clearLayer(2);
}

sf::Text MenuObject::setTextOnButton(const std::string& text, sf::RectangleShape& button) {
    sf::Color color(0, 255, 0);
    sf::Text buttonText(text, _font, 20); // Taille de texte 20
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
        if (mapButton[_MenuState][i].getGlobalBounds().contains(mousePosF)) {
            mapButton[_MenuState][i].setFillColor(sf::Color(0, 0, 255)); // Couleur de survol
        }
        else {
            mapButton[_MenuState][i].setFillColor(sf::Color(255, 0, 0)); // Couleur par défaut

        }
    }
}

const MenuObject::MenuStates MenuObject::getMenuState() const {
    return _MenuState;
}

void MenuObject::setMenuState(MenuStates MenuState) {
    _MenuState = MenuState;
}

const bool MenuObject::getIsMenu() const {
    return _isMenu;
}

void MenuObject::setIsMenu(bool isMenu) {
    _isMenu = isMenu;
}