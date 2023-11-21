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

public:
    Menu();
    ~Menu();

    void loadMenuButton(Window_s& window);
    void handleButtonClick(Window_s& window, Music &music);
    void update(Window_s& window);

    const MenuStates getMenuState() const;
    void setMenuState(MenuStates MenuState);
};