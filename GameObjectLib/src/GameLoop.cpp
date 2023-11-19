#include "GameLoop.hpp"
#include <iostream>

GameLoop::GameLoop() : _window(), _menu()
{
    // Set level to first
    level = 0;


    _menu.filMapButton(_window);


    // Load music for each level
    _music.push_back(std::make_unique<sf::Music>());
    if (!_music.back()->openFromFile("asset/music/1.mp3")) {
        std::cout << "Error loading music" << std::endl;
    }
    _music.push_back(std::make_unique<sf::Music>());
    if (!_music.back()->openFromFile("asset/music/2.mp3")) {
        std::cout << "Error loading music" << std::endl;
    }
    _music.push_back(std::make_unique<sf::Music>());
    if (!_music.back()->openFromFile("asset/music/3.mp3")) {
        std::cout << "Error loading music" << std::endl;
    }
    _music.push_back(std::make_unique<sf::Music>());
    if (!_music.back()->openFromFile("asset/music/4.mp3")) {
        std::cout << "Error loading music" << std::endl;
    }
    _music.push_back(std::make_unique<sf::Music>());
    if (!_music.back()->openFromFile("asset/music/5.mp3")) {
        std::cout << "Error loading music" << std::endl;
    }

    // Start
    _music[level]->setVolume(100);
    _music[level]->setLoop(true);
    // level 0 = menu
    _music[level]->play();
}

GameLoop::~GameLoop()
{

}

void GameLoop::run()
{
    sf::Clock clock;
    sf::View cameraView;
    //cameraView.setSize();
    // Set it to default view to hero
    //cameraView.setCenter();


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
    sf::Mouse mouse;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        mouse.getPosition();
    }

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }



    }
}

void GameLoop::nextLevel() 
{
    if (/*next level cond*/true != true) {
        _music[level]->stop();
        if (/*level not max*/true != true) {
            level += 1;
            _music[level]->play();
        }
        else {
            level = 0;
            _music[level]->play();

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
