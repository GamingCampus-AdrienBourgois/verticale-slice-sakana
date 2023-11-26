#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "Menu.hpp"
#include "Window.hpp"
#include "Music.hpp"
#include "MenuObject.hpp"
#include "GameStatistics.hpp"

class GameLoop {
public:
    GameLoop();
    ~GameLoop();

    void run();
    void nextLevel();
    void processEvents(float deltaTime, sf::View cameraView);
    void update(float deltaTime);
    void render();
private:
    unsigned int level;
    bool isMousePressed;
 
    // Ordre de declaration importante car si _window et _music sont pas declare avant _menu alors 
    // il ne seront pas initilalié lorsquon les met en parametre de _menu

    GameStatistics _gameStatistics;
    Window_s _window;
    Music _music;
    Menu _menu;



};