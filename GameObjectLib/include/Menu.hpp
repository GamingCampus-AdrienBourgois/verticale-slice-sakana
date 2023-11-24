#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Window.hpp"
#include "Music.hpp"
#include "MenuObject.hpp"
#include "Settings.hpp"

//Cette class est le menu de base elle prend les instaces de class de chauqun de ces states.
class Menu : public MenuObject 
{
    Settings _settings;

    // Les autres variables utiles sont dans MenuObject en access protected

    bool _isMenu;

public:
    Menu(Window_s& window, Music& music);
    ~Menu();

    // presque la meme chose que update car cest appeler dans la gameloop de maniere permanente sauf que celui ci gere les evenement pour pour chaque states different
    void handleEvent(const sf::Event& event, Window_s &window, Music& music);

    void loadMenuButton(Window_s& window);
    void handleButtonClick(const sf::Event& event, Window_s& window, Music &music);
    void update(Window_s& window, Music& music);

    const MenuStates getMenuState() const;
    void setMenuState(MenuStates MenuState);
    const bool getIsMenu() const;
    void setIsMenu(bool isMenu);
};