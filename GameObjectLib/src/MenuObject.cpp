#include "MenuObject.hpp"
#include <iostream>

void MenuObject::draw(Window_s& window) {
    for (size_t i = 0; i < buttons.size(); i++) {
        window.addToRenderLayer(static_cast<int>(Layer::TEXTBUTTON), buttonTexts[i]); // Add text on buttons
        window.addToRenderLayer(static_cast<int>(Layer::MENUBUTTON), buttons[i]); // Add buttons
    }
    for (size_t i = 0; i < basicTexts.size(); i++) {
        window.addToRenderLayer(static_cast<int>(Layer::TEXTRANDOM), basicTexts[i]);
    }
    for (size_t i = 0; i < bgSprt.size(); i++) {
        window.addToRenderLayer(static_cast<int>(Layer::SRITESBG), bgSprt[i]);
    }
    for (size_t i = 0; i < particles.size(); i++) {
        window.addToRenderLayer(static_cast<int>(Layer::PARTICLES), particles[i]);
    }    
    for (size_t i = 0; i < globalSprt.size(); i++) {
        window.addToRenderLayer(static_cast<int>(Layer::SPRITESGB), globalSprt[i]);
    }

}

void MenuObject::resetValues(Window_s& window) {
    buttonTexts.clear();
    buttons.clear();
    basicTexts.clear();
    bgSprt.clear();
    bgTex.clear();
    particles.clear();
    buttonCount = 0;
    window.clearLayer(static_cast<int>(Layer::SRITESBG));
    window.clearLayer(static_cast<int>(Layer::MENUBUTTON));
    window.clearLayer(static_cast<int>(Layer::TEXTBUTTON));   
    window.clearLayer(static_cast<int>(Layer::PARTICLES));
    window.clearLayer(static_cast<int>(Layer::BAR));
    window.clearLayer(static_cast<int>(Layer::HANDLE));
    window.clearLayer(static_cast<int>(Layer::TEXTSLIDER));
    window.clearLayer(static_cast<int>(Layer::TEXTRANDOM));
    window.clearLayer(static_cast<int>(Layer::SPRITESGB));
}

sf::Text MenuObject::setTextOnButton(const std::string& text, sf::RectangleShape& button, unsigned int size, sf::Color color) {
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

    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i].getGlobalBounds().contains(mousePosF)) {
            buttons[i].setFillColor(sf::Color(0, 0, 255)); // Couleur de survol
        }
        else {
            buttons[i].setFillColor(sf::Color(255, 0, 0)); // Couleur par d�faut

        }
    }
}

sf::Text MenuObject::createText(const std::string& text, const sf::Vector2f& position, unsigned int size, sf::Color color) {
    sf::Text textObject;
    textObject.setFont(_fontAny);
    textObject.setString(text);
    textObject.setCharacterSize(size);
    textObject.setFillColor(color);
    textObject.setPosition(position);

    sf::FloatRect bounds = textObject.getLocalBounds();
    textObject.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    return textObject;
}

void MenuObject::reloding(Window_s& window) {
    resetValues(window); // Detruit tout ce quil y a dans les layers et toute les valeurs (les valeurs seront remplacer par les loaders)
    load(window); // Load les bouttons
    draw(window); // Draw les boutons charg�
}
