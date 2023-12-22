#pragma once
#include <SFML/Graphics.hpp>

#include "PlayObject.hpp"
#include "Map.hpp"
#include "Fish.hpp"
#include "HumanFish.hpp"
#include "FisherMan.hpp"
#include "Props.hpp"
#include "Ath.hpp"
#include "Power.hpp"



class Play {
public:
    Play();

    ~Play();

    void draw(Window_s& window);

    void reset(Window_s& window);

    void resetStates(Window_s& window);

    void animate(float deltaTime, Window_s& window);

    void load(Window_s& window);

    void update(Window_s& window, Music& music, float deltaTime);

    void handleEvent(const sf::Event& event, Window_s& window, Music& music);

private:
    PlayObject _obj;

    Props _props;

    Ath _ath;
    Map _map;
    HumanFish _humanFish;
    Fish _fish;
    Power _power;
    FicherMan _fisherMan;

    sf::View cameraView;
    bool pause;
    bool loadOnce;
    bool loadOnceF;
    std::vector<Fish> fishs;
};
