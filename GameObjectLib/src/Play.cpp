#include "Play.hpp"

Play::Play() :
    _obj(),
    _fisherMan(_obj, cameraView),
    _map(_obj),
    _humanFish(_obj, cameraView),
    _fish(),
    _ath(_obj),
    _props(_obj),
    _power(_obj, _humanFish, _map, _props, _fish)
{
    loadOnce = false;
    loadOnceF = false;
    pause = false;
    fishs = _fish.generateFishes("Save/saveFish.txt");
    _obj._fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
}

Play::~Play() = default;

void Play::draw(Window_s& window) {
    _obj.draw(window);
}
void Play::reset(Window_s& window) {
    loadOnce = false;
    loadOnceF = false;
    _obj.resetValues(window);

}

void Play::resetStates(Window_s& window) {



    if (!_fisherMan.getIsDefFishing()) {
        // load fish part
        if (!loadOnce) {
            reset(window);
            load(window);
            draw(window);
            loadOnce = true;
            loadOnceF = false;

            // load power
            _power.setPower(_fisherMan.getPowers());
            _power.computePower();
        }

    }
    if (!loadOnceF) {

        if (_obj.globalSprt[GlobalS::HOOK].getGlobalBounds().intersects(_obj.globalSprt[GlobalS::HFISH].getGlobalBounds())) {
            reset(window);
            _fisherMan.resetValues();

            load(window);
            draw(window);
            loadOnceF = true;
            loadOnce = false;
        }
    }

}

void Play::animate(float deltaTime, Window_s& window) {
    if (pause)
        return;

    _fish.animateAllFish(deltaTime, _obj, _obj.globalSprt[GlobalS::HFISH], fishs, _humanFish);
    if (_fisherMan.getIsDefFishing())
        _fisherMan.animate(deltaTime, window);
    else {
        _humanFish.animate(deltaTime, window);
        _props.animateFishingRod(deltaTime, window);
        _props.animate(deltaTime, window);
    }



    _props.animateAlgae(deltaTime, window);
    _props.animateSpecificObstacle(deltaTime, _obj.massSprt[MassS::CANS], window);
    _props.animateSpecificObstacle(deltaTime, _obj.massSprt[MassS::WOODS], window);
    _props.animateSpecificObstacle(deltaTime, _obj.massSprt[MassS::TRASHS1], window);
    _props.animateSpecificObstacle(deltaTime, _obj.massSprt[MassS::TRASHS2], window);


    _map.animation(deltaTime);
}


void Play::load(Window_s& window) {




    _ath.load(window);
    _power.load(window);
    _map.load(window);
    if (_fisherMan.getIsDefFishing()) {
        _fisherMan.load(window);
    }
    else {
        _humanFish.load(window);
    }
    _props.load(window);
    _fish.loadTextures(_obj, fishs);

}

void Play::update(Window_s& window, Music& music, float deltaTime) {
    if (pause)
        return;



    if (_fisherMan.getIsDefFishing()) {
        _fisherMan.update(deltaTime, window);
        _fisherMan.updateCamera(deltaTime, window);
    }
    else {

        _humanFish.followMouse(window, deltaTime);
        _humanFish.updateCamera(deltaTime, window);

        _humanFish.checkAndEatAlgae(window);
        _humanFish.handleObstacleCollision(window, MassS::CANS);
        _humanFish.handleObstacleCollision(window, MassS::TRASHS1);
        _humanFish.handleObstacleCollision(window, MassS::TRASHS2);
        _humanFish.handleObstacleCollision(window, MassS::WOODS);
        _humanFish.shrinkWithTime(deltaTime);
        _humanFish.handleFishsCollision(window);

    }

    _ath.clock(deltaTime, window, cameraView);
    _power.update(window, deltaTime);
    animate(deltaTime, window);

}

void Play::handleEvent(const sf::Event& event, Window_s& window, Music& music) {

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
    _fisherMan.handleEvent(event, window, music);

    _humanFish.handleEvent(event, window);



}