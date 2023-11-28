#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Window.hpp"

class Music {
    std::vector<std::unique_ptr<sf::Music>> _music;
    float _volume;
    bool pause;

    void operator=(const std::string& musicFile);
public:
    Music();
    ~Music();

    void loadMusic();
    void playMusic(int level);
    void stopMusic(int level);
    void stopAllMusic();
    void pauseMusic();
    const std::vector<std::unique_ptr<sf::Music>>& getMusic() const;

    void setVolume(float volume);
    const float getVolume() const;
    void setPause(bool _pause);
    const bool getPause() const;
};
