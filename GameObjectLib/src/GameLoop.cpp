#include "GameLoop.hpp"

#include <iostream>
GameLoop::GameLoop() : _window(), _hero("asset/hero.png"), _labyrinth("asset/map.txt") {
    _hero.setPosition(1000, 700);
    _hero.setSize(2.2f, 2.2f);
}

void GameLoop::run() {
    sf::Clock clock;
    sf::View cameraView;
    cameraView.setSize(1600, 1000);

    _labyrinth.LoadMap(_window);
    while (_window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        cameraView.setCenter(_hero.getPosition().x + 50, _hero.getPosition().y + 50);
        _window.getWindow().setView(cameraView);
        processEvents();
        update(deltaTime);
        render();
        
    }
}

void GameLoop::processEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
        if (event.type == sf::Event::KeyPressed) {

            sf::Vector2f futurePosition = _hero.getPosition();

    
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    _hero.setDirection(0); // direction animation
                    futurePosition.y -= 10;
                    if(!_labyrinth.isCollidingWithWalls(_hero.getFeetBoundsAtPosition(futurePosition.x, futurePosition.y))) {
                        _hero.setPosition(futurePosition.x, futurePosition.y);
                    }
                    break;
                case sf::Keyboard::Down:
                    _hero.setDirection(2);
                    futurePosition.y += 10;
                    if(!_labyrinth.isCollidingWithWalls(_hero.getFeetBoundsAtPosition(futurePosition.x, futurePosition.y))) {
                        _hero.setPosition(futurePosition.x, futurePosition.y);
                    }
                    break;
                case sf::Keyboard::Left:
                    _hero.setDirection(1);
                    futurePosition.x -= 10;
                    if(!_labyrinth.isCollidingWithWalls(_hero.getFeetBoundsAtPosition(futurePosition.x, futurePosition.y))) {
                        _hero.setPosition(futurePosition.x, futurePosition.y);
                    }
                    break;
                case sf::Keyboard::Right:
                    _hero.setDirection(3);
                    futurePosition.x += 10;
                    if(!_labyrinth.isCollidingWithWalls(_hero.getFeetBoundsAtPosition(futurePosition.x, futurePosition.y))) {
                        _hero.setPosition(futurePosition.x, futurePosition.y);
                    }
                    break;
                default:
                    _hero.stop();
                    break;
            }
        }
    }
}


void GameLoop::update(float deltaTime) {
    _hero.update(deltaTime);
}

void GameLoop::render() {
    _window.clear();
    _hero.draw(_window);
    _window.renderLayers();
    _window.display();

}
