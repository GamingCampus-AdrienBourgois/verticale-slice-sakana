#pragma once
#include <SFML/Graphics.hpp>

#include "PlayObject.hpp"
#include "Map.hpp"
#include "Fish.hpp"
#include "HumanFish.hpp"

class Play  {
    PlayObject _obj;

    Map _map;
    Fish _fish;
    HumanFish _humanFish;

    bool loaded;
public:
    Play() :
    _obj(),
    _map(_obj),
    _fish(),
    _humanFish(_obj)
    {
        loaded = false;
        _obj._fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
    }


	~Play() = default;

    void draw(Window_s &window) {

        _obj.draw(window);
    }

    void animate(float deltaTime, Window_s &window) {
        _humanFish.animate(deltaTime, window);
    }



    void load(Window_s& window) {


        _humanFish.load(window);
        _map.load(window);

    }



    void update(Window_s& window, Music& music, float deltaTime) {
        _humanFish.followMouse(window, deltaTime);
        _humanFish.animate(deltaTime, window);
    }
    void handleEvent(const sf::Event& event, Window_s& window, Music& music) {
        _humanFish.handleEvent(event, window, music);
    }
};