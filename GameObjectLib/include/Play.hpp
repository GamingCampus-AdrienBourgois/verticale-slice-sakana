#pragma once
#include <SFML/Graphics.hpp>

#include "PlayObject.hpp"
#include "Map.hpp"
#include "Fish.hpp"
#include "HumanFish.hpp"
#include "FisherMan.hpp"
#include "Props.hpp"

class Play  {
    PlayObject _obj;

    Map _map;
    Fish _fish;
    HumanFish _humanFish;
    Props _props;

    std::vector<Fish> fishs;
public:
    Play() :
    _obj(),
    _fish(),
    _map(_obj),
    _props(_obj),
    _humanFish(_obj)
    {
        fishs = _fish.generateFishes("Save/saveFish.txt");
        _obj._fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
    }

	~Play() = default;

    void draw(Window_s &window) {
        _obj.draw(window);
    }

    void animate(float deltaTime, Window_s &window) {
        _humanFish.animate(deltaTime, window);
        _fish.animateAllFish(deltaTime, _obj, _obj.globalSprt[GlobalS::HFISH], fishs);
        _props.animateAlgae(deltaTime, window);
    }

    void load(Window_s& window) {
        _map.load(window);
        _fish.loadTextures(_obj, fishs);
        _humanFish.load(window);
        _props.load(window);
    }

    void update(Window_s& window, Music& music, float deltaTime) {
        _humanFish.followMouse(window, deltaTime);
        _humanFish.updateCamera(deltaTime, window);
        animate(deltaTime, window);
    }

    void handleEvent(const sf::Event& event, Window_s& window, Music& music) {
        _humanFish.handleEvent(event, window);
    }
};