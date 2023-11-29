#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include <iostream>


#include "Window.hpp"
#include "Play.hpp"
#include "Music.hpp"
#include "MenuObject.hpp"
#include "Settings.hpp"
#include "Help.hpp"
#include "Credit.hpp"
#include "Success.hpp"


// Cette class est le menu de base elle prend les instaces de class de chauqun de ces states.
class Menu : public MenuObject 
{
    Settings _settings;
    Credit _credit;
    Help _help;
    Success _success;
    Play _play;

    // Les autres variables utiles sont dans MenuObject en access protected
    float elapsed;

    int raindrops = 500;

    bool _isMenu;
    MenuStates _MenuState;
    MenuStates _PreviousMenuState;
 
public:
    Menu(Window_s& window, Music& music);
    ~Menu();

    void handleEvent(const sf::Event& event, Window_s &window, Music& music);
    void load(Window_s& window);
    void handleButtonClick(const sf::Event& event, Window_s& window, Music &music);
    void update(Window_s& window, Music& music, float deltaTime);
    void textureSetters(Window_s &window);
    void rainAnim(float deltaTime, Window_s& window);
    void reloadByState(Window_s& window);

    const MenuStates getMenuState() const;
    void setMenuState(MenuStates MenuState);
    const bool getIsMenu() const;
    void setIsMenu(bool isMenu);
};