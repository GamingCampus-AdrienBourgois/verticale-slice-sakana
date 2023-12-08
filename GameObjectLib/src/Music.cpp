#include "Music.hpp"
#include <iostream>

Music::Music() : _volume(100), pause(false)
{

}

Music::~Music() = default;

// Utilisation de this :
// loadMusic() == loadMusic(Music *this)
// *this == this[0] (premiere instance de Music qui sera toujours le constructeur)
void Music::loadMusic() 
{
    *this = "asset/music/1.mp3";
    *this = "asset/music/2.mp3";
    *this = "asset/music/3.mp3";
    *this = "asset/music/4.mp3";
    *this = "asset/music/5.mp3";
    *this = "asset/music/6.mp3";

}

void Music::playMusic(int level) 
{
    if (pause)
        return;

    if (level >= 0 && level < _music.size()) {
        _music[level]->setVolume(_volume);
        _music[level]->setLoop(true);
        _music[level]->play();

    }
    else {
        std::cerr << "level out of range" << std::endl;
    }
}

void Music::setVolume(float volume) {
    for (auto& musics : _music) {
        musics->setVolume(volume);
    }
    _volume = volume;
}

const float Music::getVolume() const {
    return _volume;
}

void Music::stopMusic(int level) {
    if (level >= 0 && level < _music.size()) {
        _music[level]->stop();
    }
    else {
        std::cerr << "level out of range" << std::endl;
    }
}

void Music::stopAllMusic() {
    for (auto& music : _music) {
        if (music->getStatus() == sf::Music::Playing) {
            music->stop();
            break;
        }
    }
}

const std::vector<std::unique_ptr<sf::Music>>& Music::getMusic() const {
    return _music;
}

void Music::pauseMusic() {
    for (auto& music : _music) {
        if (music->getStatus() == sf::Music::Playing) {
            music->pause();
            break;
        }
    }
}

void Music::setPause(bool _pause)
{
    pause = _pause;
}

const bool Music::getPause() const
{
    return pause;
}

void Music::operator=(const std::string& musicFile) {
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(musicFile)) {
        std::cout << "Error loading music from: " << musicFile << std::endl;
        return;
    }
    music->setVolume(_volume);
    _music.push_back(std::move(music));
}