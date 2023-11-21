#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

#include "Window.hpp"

class Window_s; // Déclaration anticipée

// Classe de base abstraite pour les objets de menu
class MenuBase {
public:
    virtual ~MenuBase() {}

    virtual void draw(Window_s& window);
    virtual void resetValues(Window_s& window);

    enum MenuStates {
        BASE,
        PLAY,
        SETTINGS,
        HELP,
        SUCCESS,
        CREDIT,
        QUIT
    };

protected:
    sf::Text setTextOnButton(const std::string& text, sf::RectangleShape& button);

    sf::Font _font;
    unsigned int buttonCount;
    std::vector<sf::Text> buttonTexts;
    std::map<std::string, std::vector<sf::RectangleShape>> mapButton;
    MenuStates _MenuState;
};



void MenuBase::draw(Window_s& window) {
    for (unsigned int i = 0; i < buttonCount; i++) {
        window.addToRenderLayer(2, buttonTexts[i]); // Add text on buttons
        window.addToRenderLayer(1, mapButton[_MenuState][i]); // Add buttons
    }
}

void MenuBase::resetValues(Window_s& window) {
    buttonTexts.clear();
    for (auto& stateButtons : mapButton) {
        stateButtons.second.clear();
    }
    buttonCount = 0;
    window.clearLayer(1);
    window.clearLayer(2);
}

sf::Text MenuBase::setTextOnButton(const std::string& text, sf::RectangleShape& button) {
    sf::Color color(0, 255, 0);
    sf::Text buttonText(text, _font, 20); // Taille de texte 20
    buttonText.setFillColor(color);
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(button.getPosition());
    return buttonText;
}
