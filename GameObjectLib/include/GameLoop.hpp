#pragma once
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include "Window.hpp"
#include "Labyrinth.hpp"
#include "Enemy.hpp"

class GameLoop {
public:
    GameLoop();

    void run();

private:
    Enemy _monster;
    Window_s _window;
    Character _hero;
    Labyrinth _labyrinth;

    float _elapsedTime;

    void processEvents(float deltaTime, sf::View cameraView);
    void update(float deltaTime);
    void render();
};
