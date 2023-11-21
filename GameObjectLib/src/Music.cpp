#include "Music.hpp"
#include <iostream>

Music::Music() = default;
Music::~Music() = default;

void Music::LoadMusic() 
{
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
}

void Music::setAllVolume(float volume) {
    for (auto& musics : _music) {
        musics->setVolume(volume);
    }
}

void Music::playMusic(int level) {
    if (level >= 0 && level < _music.size()) {
        _music[level]->setVolume(100);
        _music[level]->setLoop(true);
        _music[level]->play();
    }
    else {
        std::cerr << "level out of range" << std::endl;
    }
}

void Music::setVolume(int level, float volume) {
    if (level >= 0 && level < _music.size()) {
        _music[level]->setVolume(volume);
    }
    else {
        std::cerr << "level out of range" << std::endl;
    }
}

void Music::stopMusic(int level) {
    if (level >= 0 && level < _music.size()) {
        _music[level]->stop();
    }
    else {
        std::cerr << "level out of range" << std::endl;
    }
}

const std::vector<std::unique_ptr<sf::Music>>& Music::getMusic() const {
    return _music;
}
