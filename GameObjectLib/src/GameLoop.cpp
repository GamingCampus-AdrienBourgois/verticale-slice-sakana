#include "GameLoop.hpp"
#include "Path.hpp"
#include <iostream>

GameLoop::GameLoop() : _window(), _hero("asset/hero.png"), _labyrinth("asset/map.txt"), _monster("asset/ghost.png") {
    _hero.setPosition(Wall::HEIGHT * Wall::SIZE + (Wall::HEIGHT * Wall::SIZE) / 3, Wall::HEIGHT * Wall::SIZE + (Wall::HEIGHT * Wall::SIZE) / 3);

    _hero.setSize(2.2f, 2.2f);
    _monster.setPosition(1000, 300);
    _monster.setSize(0.06f, 0.06f);
}

void GameLoop::run() {
    sf::Clock clock;
    sf::View cameraView;
    cameraView.setSize(1600, 1000);

    _labyrinth.LoadMap(_window);
    while (_window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        cameraView.setCenter(_monster.getPosition().x + 50, _monster.getPosition().y + 50);
        _window.getWindow().setView(cameraView);
        processEvents();
        update(deltaTime);
        render();

    }
}

void GameLoop::processEvents() 
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
        _monster.move(_labyrinth.getMatrice(), _hero);
        _hero.move(event, _labyrinth);
    }
}



void GameLoop::update(float deltaTime) {
    _hero.update(deltaTime);
    //_monster.update(deltaTime);
}

void GameLoop::render() {
    _window.clear();
    _monster.draw(_window);
    _hero.draw(_window);
    _window.renderLayers();
    _window.display();

}
