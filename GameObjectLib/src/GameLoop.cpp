#include "GameLoop.hpp"
#include "Path.hpp"
#include <iostream>


GameLoop::GameLoop() : _window(), _hero("asset/hero.png"), _monster("asset/ghost.png") {

    // Set level to first
    level = 0;





    


    // Set map for  5 levels
    //_labyrinth.resize(5);
    _labyrinth.push_back(new Labyrinth("asset/map.txt"));
    _labyrinth.push_back(new Labyrinth("asset/map1.txt"));
    _labyrinth.push_back(new Labyrinth("asset/map2.txt"));
    _labyrinth.push_back(new Labyrinth("asset/map3.txt"));
    _labyrinth.push_back(new Labyrinth("asset/map4.txt"));



    // Sprite init
    _hero.setPosition((Wall::HEIGHT * Wall::SIZE * 1) + (Wall::HEIGHT * Wall::SIZE) / 2, (Wall::HEIGHT * Wall::SIZE * 1) + (Wall::HEIGHT * Wall::SIZE) / 2);
    _hero.setSize(2.2f, 2.2f);



    //_music.resize(5); // 5 level
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


    _music[level]->play();
    _music[level]->setVolume(100);
    _music[level]->setLoop(true);



}

GameLoop::~GameLoop() {
    for (auto labyrinth : _labyrinth) {
        delete labyrinth;
    }
}


void GameLoop::run() {
    sf::Clock clock;
    sf::View cameraView;
    cameraView.setSize(1600, 1000);

    // Set it to default view 
    cameraView.setCenter(_hero.getPosition().x + 50, _hero.getPosition().y + 50);
    _window.getWindow().setView(cameraView);


    _labyrinth[level]->LoadMap(_window);


    // Sprite init here because load map needed
    int monsterSety = _labyrinth[level]->getMatrice().size(); // Pos the enemie at the 2nd last cell
    int monsterSetx = _labyrinth[level]->getMatrice()[_labyrinth[level]->getMatrice().size() - 1].size();

    //std::cout << monsterSetx << " - " << monsterSety << std::endl;
    _monster.setPosition(((Wall::HEIGHT * Wall::SIZE) * (monsterSetx - 2)) + ((Wall::HEIGHT * Wall::SIZE) / 2), ((Wall::HEIGHT * Wall::SIZE) * (monsterSety - 2)) + ((Wall::HEIGHT * Wall::SIZE) / 2));
    _monster.setSize(1.4f, 1.4f);



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
        if (event.type == sf::Event::Closed) {
            _window.close();
        }


    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        cameraView.setCenter(_monster.getPosition().x + 50, _monster.getPosition().y + 50);
        _window.getWindow().setView(cameraView);
    }
    else {
        cameraView.setCenter(_hero.getPosition().x + 50, _hero.getPosition().y + 50);
        _window.getWindow().setView(cameraView);
    }



}

void GameLoop::nextLevel() {



    if (_hero.offGrid(*(_labyrinth[level])) ) {
        _music[level]->stop();
        if (level < _labyrinth.size() - 1) {
            level += 1;

            _labyrinth[level]->LoadMap(_window);

            _music[level]->play();


            _hero.setPosition((Wall::HEIGHT * Wall::SIZE * 1) + (Wall::HEIGHT * Wall::SIZE) / 2, (Wall::HEIGHT * Wall::SIZE * 1) + (Wall::HEIGHT * Wall::SIZE) / 2);


            int monsterSety = _labyrinth[level]->getMatrice().size(); // Pos the enemie at the 2nd last cell
            int monsterSetx = _labyrinth[level]->getMatrice()[_labyrinth[level]->getMatrice().size() - 1].size();

            //std::cout << monsterSetx << " - " << monsterSety << std::endl;
            _monster.setPosition(((Wall::HEIGHT * Wall::SIZE) * (monsterSetx - 2)) + ((Wall::HEIGHT * Wall::SIZE) / 2), ((Wall::HEIGHT * Wall::SIZE) * (monsterSety - 2)) + ((Wall::HEIGHT * Wall::SIZE) / 2));
        }
        else {
            level = 0;
            _music[level]->play();

        }

    }
    //std::cout << _labyrinth[level]->getMatrice().size() - 1 << " - " << _labyrinth[level]->getMatrice()[_labyrinth[level]->getMatrice().size() - 2].size();
}

void GameLoop::update(float deltaTime) {
    // For animation
    _hero.update(deltaTime);
    //_monster.update(deltaTime);


    //std::cout << level << std::endl;
    // For moving
    _hero.move(deltaTime, *(_labyrinth[level]));
    _monster.move(_labyrinth[level]->getMatrice(), _hero, deltaTime);
}

void GameLoop::render() {
    _window.clear();
    _monster.draw(_window);
    _hero.draw(_window);
    _window.renderLayers();
    _window.display();

}
