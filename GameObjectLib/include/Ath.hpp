#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"

class Ath {
    PlayObject& _obj;
    float totalTime;

public:
    Ath(PlayObject& obj);

    void load(Window_s& window);
    void clock(float deltaTime, Window_s& window, sf::View& cameraView);
    void pause(Window_s& window, sf::View& cameraView);
    void unpause(Window_s& window);
};
