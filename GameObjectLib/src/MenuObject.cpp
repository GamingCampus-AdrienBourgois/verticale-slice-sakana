#include "MenuObject.hpp"
#include <iostream>

void MenuObject::draw(Window_s& window) {
    for (unsigned int i = 0; i < buttonCount; i++) {
        window.addToRenderLayer(static_cast<int>(Layer::TEXTBUTTON), buttonTexts[i]); // Add text on buttons
        window.addToRenderLayer(static_cast<int>(Layer::MENUB), mapButton[i]); // Add buttons
    }
    for (size_t i = 0; i < basicTexts.size(); i++) {
        window.addToRenderLayer(static_cast<int>(Layer::TEXTRANDOM), basicTexts[i]);
    }
}

void MenuObject::resetValues(Window_s& window) {
    buttonTexts.clear();
    mapButton.clear();
    basicTexts.clear();
    buttonCount = 0;
    window.clearLayer(static_cast<int>(Layer::MENUB));
    window.clearLayer(static_cast<int>(Layer::TEXTBUTTON));
    window.clearLayer(static_cast<int>(Layer::BAR));
    window.clearLayer(static_cast<int>(Layer::HANDLE));
    window.clearLayer(static_cast<int>(Layer::TEXTSLIDER));
    window.clearLayer(static_cast<int>(Layer::TEXTRANDOM));

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

void MenuObject::reloding(Window_s& window) {
    resetValues(window); // Detruit tout ce quil y a dans les layers et toute les valeurs (les valeurs seront remplacer par les loaders)
    load(window); // Load les bouttons
    draw(window); // Draw les boutons chargé
}
