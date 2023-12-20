#pragma once
#include <SFML/Graphics.hpp>

#include "PlayObject.hpp"
#include "Map.hpp"
#include "Fish.hpp"
#include "HumanFish.hpp"
#include "FisherMan.hpp"

class Play  {
    PlayObject _obj;

    Map _map;
    Fish _fish;
    HumanFish _humanFish;
    FicherMan _ficherMan;

    std::vector<Fish> fishs;
    bool loaded;
public:
    Play() :
        _obj(),
        _map(_obj),
        _fish(),
        _ficherMan(_obj),
        _humanFish(_obj)
    {
        loaded = false;
        fishs = _fish.generateFishes("Save/saveFish.txt");
        _obj._fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
    }


	~Play() = default;

    void draw(Window_s &window) {

        _obj.draw(window);
    }

    void animate(float deltaTime, Window_s &window) {

        _ficherMan.animate(deltaTime, window);
        /*
        _humanFish.animate(deltaTime, window);
        // animate each fish
        int fishIdx = 0;
        for (size_t i = GlobalS::FISHA; i < GlobalS::GEND; i++) {

            //fishs[fishIdx].moveAI(deltaTime, _obj, i, _obj.globalSprt[GlobalS::HFISH]);
            fishs[fishIdx].animate(deltaTime, _obj, i);
            fishIdx++;
        }*/
    }



    void load(Window_s& window) {
        /*
        _map.load(window);

        for (size_t i = GlobalS::FISHA; i < GlobalS::GEND; i++) {
            _fish.loadTextures(_obj, i, fishs);
        }

        _humanFish.load(window);*/
        _ficherMan.load(window);
    }



    void update(Window_s& window, Music& music, float deltaTime) {
        //_humanFish.followMouse(window, deltaTime);
        _ficherMan.followMouse(window, deltaTime);
        _ficherMan.update(deltaTime, window);
        animate(deltaTime, window);
    }
    void handleEvent(const sf::Event& event, Window_s& window, Music& music) {
        //_humanFish.handleEvent(event, window, music);
        _ficherMan.handleEvent(event, window, music);
    }
};