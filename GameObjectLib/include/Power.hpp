#pragma once

#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include "HumanFish.hpp"
#include "Map.hpp"
#include "Props.hpp"
#include "Fish.hpp"

class Power {
    PlayObject& _obj;

    HumanFish& humanFish;
    Map& map;
    Props& props;
    Fish& fish;

    std::vector<int> power;

    float elapsed;

    bool dash;
    bool cloak;
    bool size;
    bool food;
    bool speed;
    bool jump;
    bool impress;
    bool vision;
    bool killer;

public:
    Power(PlayObject& obj, HumanFish& _humanFish, Map& _map, Props& _prop, Fish& _fish);
    ~Power();
    void setPower(std::vector<int> _power);
    void update(Window_s& window, float deltaTime);
    void computePower();
    void load(Window_s& window);
    void handleEvent(const sf::Event& event, Window_s& window, Music& music);
    void Dash(Window_s& window, float deltaTime);
    void Cloak(Window_s& window, float deltaTime);
    void Size(Window_s& window);
    void Food(Window_s& window);
    void Speed(Window_s& window);
    void Jump(Window_s& window, float deltaTime);
    void Impress(Window_s& window);
    void Vision(Window_s& window, float deltaTime);
    void Killer(Window_s& window);
    void setDash();
    void setCloak();
    void setSize();
    void setFood();
    void setSpeed();
    void setJump();
    void setImpress();
    void setVision();
    void setKiller();
};
