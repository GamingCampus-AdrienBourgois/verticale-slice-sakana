#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Window.hpp"

class Music {
    std::vector<std::unique_ptr<sf::Music>> _music;

public:
    Music();
    ~Music();

    void LoadMusic();
    void playMusic(int level);
    void setVolume(int level, float volume);
    void stopMusic(int level);
    const std::vector<std::unique_ptr<sf::Music>>& getMusic() const;
};
