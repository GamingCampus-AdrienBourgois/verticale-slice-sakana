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
    virtual sf::Text setTextOnButton(const std::string& text, sf::RectangleShape& button);
    virtual void changeOnMouse(Window_s& window);

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
    virtual const bool getIsMenu() const;
    virtual void setIsMenu(bool isMenu);

protected:
    sf::Font _font;
    unsigned int buttonCount;
    std::vector<sf::Text> buttonTexts;
    std::map<MenuStates, std::vector<sf::RectangleShape>> mapButton;

    MenuStates _MenuState;
    bool _isMenu;
};
