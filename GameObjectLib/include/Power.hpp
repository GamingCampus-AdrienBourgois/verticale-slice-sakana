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
    Power(PlayObject& obj, HumanFish& _humanFish, Map& _map, Props& _prop, Fish& _fish) :
        _obj(obj),
        humanFish(_humanFish),
        map(_map),
        props(_prop),
        fish(_fish)
    {
        elapsed = 0.f;

        dash = false;
        cloak = false;
        size = false;
        food = false;
        speed = false;
        jump = false;
        impress = false;
        vision = false;
        killer = false;

        //dash = true;
        //cloak = true;
        //size = true;
        //food = true;
        //speed = true;
        //jump = true;
        impress = true;
        //vision = true;
        killer = true;
    }

    ~Power() = default;

    void update(Window_s& window, float deltaTime) {
        if (dash) { Dash(window, deltaTime); }
        if (cloak) { Cloak(window, deltaTime); }
        if (jump) { Jump(window, deltaTime); }
        if (vision) { Vision(window, deltaTime); }
    }

    void load(Window_s& window) {

        if (size) { Size(window); }
        if (food) { Food(window); }
        if (speed) { Speed(window); }
        if (impress) { Impress(window); }
        if (killer) { Killer(window); }



    }

    void handleEvent(const sf::Event& event, Window_s& window, Music& music) {}


    void Dash(Window_s& window, float deltaTime)
    {
        humanFish.pusher(window, deltaTime, false);
    }

    void Cloak(Window_s& window, float deltaTime)
    {
        humanFish.setCloack();
    }

    void Size(Window_s& window)
    {
        _obj.globalSprt[GlobalS::HFISH].setScale(sf::Vector2f(7.f, 7.f));
    }

    void Food(Window_s& window)
    {
        props.setAlgae(props.getAlgae() * 1.5f);
    }

    void Speed(Window_s& window)
    {
        humanFish.setSpeed(1.5f);
    }

    void Jump(Window_s& window, float deltaTime)
    {
        humanFish.pusher(window, deltaTime, true);
    }

    void Impress(Window_s& window) 
    {
        fish.setFocus(fish.getFocus() / 2.f);
    }

    void Vision(Window_s& window, float deltaTime)
    {
        humanFish.applyAuraEffect(window);
    }

    void Killer(Window_s& window) {}

    void setDash() {
        dash = !dash;
    }

    void setCloak() {
        cloak = !cloak;
    }

    void setSize() {
        size = !size;
    }

    void setFood() {
        food = !food;
    }

    void setSpeed() {
        speed = !speed;
    }

    void setJump() {
        jump = !jump;
    }

    void setImpress() {
        impress = !impress;
    }

    void setVision() {
        vision = !vision;
    }

    void setKiller() {
        killer = !killer;
    }
};
