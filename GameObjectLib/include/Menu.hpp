#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Window.hpp"
#include "Music.hpp"
#include "Settings.hpp"


class Menu {
public:
    Menu();
    ~Menu();

    enum MenuStates {
        BASE,
        PLAY,
        SETTINGS,
        HELP,
        SUCCESS,
        CREDIT,
        QUIT
    };

    void draw(Window_s& window);
    void LoadMenuButton(Window_s& window);
    void handleButtonClick(Window_s& window, Music &music);
    void resetValues(Window_s& window);

    const MenuStates getMenuState() const;
    void setMenuState(MenuStates MenuState);
    const bool getIsMenu() const;
    void setIsMenu(bool isMenu);
    sf::Text setTextOnButton(const std::string& text, sf::RectangleShape& button);

private:
    // Menu
    bool _isMenu;
    MenuStates _MenuState;

    // Buttons gestion
    sf::Font _font;
    unsigned int buttonCount;
    std::vector<sf::Text> buttonTexts;
    std::map<MenuStates, std::vector<sf::RectangleShape>> mapButton;

    // Menu states


};