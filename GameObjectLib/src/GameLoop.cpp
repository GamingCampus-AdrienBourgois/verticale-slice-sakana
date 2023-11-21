#include "GameLoop.hpp"
#include <iostream>

GameLoop::GameLoop() : _window(), _menu(), _music()
{
    // Set level to first
    level = 0;
    

    // Load menu
    _menu.LoadMenuButton(_window);
    // Base Menu draw
    _menu.draw(_window);


    // Load music for each level
    _music.LoadMusic();
    // Music player and level 0 = menu music
    _music.playMusic(level);
}

GameLoop::~GameLoop()
{

}

void GameLoop::run()
{
    sf::Clock clock;
    sf::View cameraView;

    while (_window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents(deltaTime, cameraView);
        update(deltaTime);
        nextLevel();
        render();
    }
}

void GameLoop::processEvents(float deltaTime, sf::View cameraView)
{
    sf::Event event;

    while (_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            _window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                _window.close();
            }
            if (event.key.code == sf::Keyboard::Return) {
                _menu.resetValues(_window);
                _menu.LoadMenuButton(_window);
                _menu.draw(_window);
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                _menu.handleButtonClick(_window, _music);
            }
            break;
        case sf::Event::Resized:
            _menu.resetValues(_window);
            _menu.LoadMenuButton(_window);
            _menu.draw(_window);
        }
    }
}


void GameLoop::nextLevel() 
{
    if (/*next level cond*/true != true) {
        _music.stopMusic(level);
        if (/*level not max*/true != true) {
            level += 1;
            _music.playMusic(level);
        }
        else {
            level = 0;
            _music.playMusic(level);

        }
    }
}

void GameLoop::update(float deltaTime) 
{

}

void GameLoop::render() 
{
    _window.clear();
    _window.renderLayers();
    _window.display();
}
