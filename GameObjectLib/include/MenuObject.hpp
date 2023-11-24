#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

#include "Window.hpp"

class Window_s; // Déclaration anticipée

// Classe de base abstraite pour les objets de menu
// Elle sert pour la creation des boutons avec draw et setTextOnButton ainsi que la reinitialisation des états avec resetValues
class MenuObject {
public:
    virtual ~MenuObject() = default;

    virtual void draw(Window_s& window);
    virtual void resetValues(Window_s& window);
    virtual sf::Text setTextOnButton(const std::string& text, sf::RectangleShape& button, unsigned int size);
    virtual void changeOnMouse(Window_s& window);
    virtual sf::Text createText(const std::string& text, const sf::Vector2f& position, unsigned int size);

    enum MenuStates {
        BASE,
        PLAY,
        SETTINGS,
        HELP,
        SUCCESS,
        CREDIT,
        QUIT
    };

    virtual const MenuStates getMenuState() const;
    virtual void setMenuState(MenuStates MenuState);

protected:
    sf::Font _fontButton;
    sf::Font _fontAny;

    unsigned int buttonCount;
    std::vector<sf::Text> buttonTexts; // texts on the buttons
    std::vector<sf::RectangleShape> mapButton; // buttons for each states

    std::vector<sf::Text> basicTexts; // texts for anything

    MenuStates _MenuState;

};
