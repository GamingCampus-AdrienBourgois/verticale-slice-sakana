#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include "Fish.hpp"

class Map {
    PlayObject& _obj;
    int frame;
    float elapsed;

public:
    Map(PlayObject& obj);
    void textureSetters(Window_s& window);
    void load(Window_s& window);
    void animation(float deltaTime);
};
