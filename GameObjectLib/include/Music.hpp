#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Window.hpp"

class Music {
    std::vector<std::unique_ptr<sf::Music>> _music;
    float _volume;
public:
    Music();
    ~Music();

    void LoadMusic();
    void playMusic(int level);
    void stopMusic(int level);
    const std::vector<std::unique_ptr<sf::Music>>& getMusic() const;
    // Music idx attribution:
    // 1 Menu
    // 2 Credit
    // 3 Gmae

    void setVolume(float volume);
    const float getVolume() const;
};
