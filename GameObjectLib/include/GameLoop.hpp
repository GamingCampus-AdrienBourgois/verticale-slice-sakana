#pragma once
#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include "Window.hpp"
#include "Labyrinth.hpp"
#include "Enemy.hpp"
#include <SFML/Audio.hpp>
#include <memory>

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

    Enemy _monster;
    Window_s _window;
    Character _hero;

    std::vector<std::unique_ptr<sf::Music>> _music;

    std::vector<Labyrinth*> _labyrinth;



};
