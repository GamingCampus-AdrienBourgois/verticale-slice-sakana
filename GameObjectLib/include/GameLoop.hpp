#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "Menu.hpp"
#include "Window.hpp"
#include "Music.hpp"

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

    Music _music;
    Menu _menu;
    Window_s _window;


};