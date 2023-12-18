#pragma once
#include <SFML/Graphics.hpp>

#include "PlayObject.hpp"
#include "Map.hpp"
#include "Fish.hpp"
#include "HumanFish.hpp"
#include "FisherMan.hpp"
#include "Props.hpp"
#include "Powers.hpp"
#include "Ath.hpp"

class Play  {
    PlayObject _obj;


    Props _props;

    Ath _ath;
    Map _map;
    Fish _fish;
    HumanFish _humanFish;
    Power _power;

    sf::View cameraView;
    bool pause;
    std::vector<Fish> fishs;
public:


    Play() :
    _obj(),
    _fish(),
    _map(_obj),
    _props(_obj),
    _humanFish(_obj, cameraView),
    _ath(_obj),
    _power(_obj, _humanFish, _map, _props, _fish)
    {

        pause = false;
        fishs = _fish.generateFishes("Save/saveFish.txt");
        _obj._fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
    }

	~Play() = default;

    void draw(Window_s &window) {
        _obj.draw(window);
    }
    void reset(Window_s& window) {
        _obj.resetValues(window);
    }

    void animate(float deltaTime, Window_s &window) {
        if (pause)
            return;

        _humanFish.animate(deltaTime, window);
        _fish.animateAllFish(deltaTime, _obj, _obj.globalSprt[GlobalS::HFISH], fishs);
        _props.animate(deltaTime, window);
        _map.animation(deltaTime);
    }


    void load(Window_s& window) {
        _power.load(window);

        _map.load(window);
        _fish.loadTextures(_obj, fishs);
        _humanFish.load(window);
        _props.load(window);
        _ath.load(window);
    }

    void update(Window_s& window, Music& music, float deltaTime) {
        if (pause)
            return;

        _humanFish.followMouse(window, deltaTime);
        _humanFish.updateCamera(deltaTime, window);
        _humanFish.checkAndEatAlgae(window);
        _humanFish.handleObstacleCollision(window, MassS::CANS);
        _humanFish.handleObstacleCollision(window, MassS::TRASHS1);
        _humanFish.handleObstacleCollision(window, MassS::TRASHS2);
        _humanFish.handleObstacleCollision(window, MassS::WOODS);
        _humanFish.shrinkWithTime(deltaTime);
        _humanFish.handleFishsCollision(window);
        _ath.clock(deltaTime, window, cameraView);
        _power.update(window, deltaTime);
        animate(deltaTime, window);
    }

    void handleEvent(const sf::Event& event, Window_s& window, Music& music) {
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::P) {
            pause = !pause;
            if (pause) {
                _ath.pause(window, cameraView);
            }
            else {

                _ath.unpause(window);
            }

        }


        if (pause)
            return;
        _humanFish.handleEvent(event, window);

    }
};