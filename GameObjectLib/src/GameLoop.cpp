#include "GameLoop.hpp"
#include <iostream>

GameLoop::GameLoop() : _window(static_cast<std::string>("game")), _music(), _menu(_window, _music)
{
    // Set level to first
    level = 0;
    

    // Load menu
    _menu.load(_window);
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
            break;
        case sf::Event::MouseButtonPressed:
            break;
        case sf::Event::Resized:
            sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            _window.getWindow().setView(sf::View(visibleArea));
        }
        
        _menu.handleEvent(event, _window, _music);
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
    _menu.update(_window, _music, deltaTime);
}

void GameLoop::render() 
{
    _window.clear();
    _window.renderLayers();
    _window.display();
}
