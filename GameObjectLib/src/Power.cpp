#include "Power.hpp"

Power::Power(PlayObject& obj, HumanFish& _humanFish, Map& _map, Props& _prop, Fish& _fish) :
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

}


Power::~Power() = default;

void Power::setPower(std::vector<int> _power) {
    power = _power;
}

void Power::update(Window_s& window, float deltaTime) {
    if (dash) { Dash(window, deltaTime); }
    if (cloak) { Cloak(window, deltaTime); }
    if (jump) { Jump(window, deltaTime); }
    if (vision) { Vision(window, deltaTime); }
    if (killer) { Killer(window); }

}

void Power::computePower() {
    for (const auto& pow : power) {
        switch (pow)
        {
        case static_cast<int>(GlobalS::FISHA):
            setDash();
            break;

        case static_cast<int>(GlobalS::FISHB):
            setCloak();
            break;

        case static_cast<int>(GlobalS::FISHC):
            setSize();
            break;

        case static_cast<int>(GlobalS::FISHD):
            setFood();
            break;

        case static_cast<int>(GlobalS::FISHE):
            setSpeed();
            break;

        case static_cast<int>(GlobalS::FISHF):
            setJump();
            break;

        case static_cast<int>(GlobalS::FISHG):
            setImpress();
            break;

        case static_cast<int>(GlobalS::FISHH):
            setVision();
            break;

        case static_cast<int>(GlobalS::FISHI):
            setKiller();
            break;
        }

    }
}

void Power::load(Window_s& window) {

    if (size) { Size(window); }
    if (food) { Food(window); }
    if (speed) { Speed(window); }
    if (impress) { Impress(window); }




}

void Power::handleEvent(const sf::Event& event, Window_s& window, Music& music) {}


void Power::Dash(Window_s& window, float deltaTime)
{
    humanFish.pusher(window, deltaTime, false);
}

void Power::Cloak(Window_s& window, float deltaTime)
{
    humanFish.setCloack();
}

void Power::Size(Window_s& window)
{
    _obj.globalSprt[GlobalS::HFISH].setScale(sf::Vector2f(7.f, 7.f));
}

void Power::Food(Window_s& window)
{
    props.setAlgae(static_cast<int>(static_cast<float>(props.getAlgae()) * 1.5f));
}

void Power::Speed(Window_s& window)
{
    humanFish.setSpeed(1.5f);
}

void Power::Jump(Window_s& window, float deltaTime)
{
    humanFish.pusher(window, deltaTime, true);
}

void Power::Impress(Window_s& window)
{
    fish.setFocus(fish.getFocus() / 2.f);
}

void Power::Vision(Window_s& window, float deltaTime)
{
    humanFish.applyAuraEffect(window);
}

void Power::Killer(Window_s& window)
{
    humanFish.killer(window);
}

void Power::setDash() {
    dash = !dash;
}

void Power::setCloak() {
    cloak = !cloak;
}

void Power::setSize() {
    size = !size;
}

void Power::setFood() {
    food = !food;
}

void Power::setSpeed() {
    speed = !speed;
}

void Power::setJump() {
    jump = !jump;
}

void Power::setImpress() {
    impress = !impress;
}

void Power::setVision() {
    vision = !vision;
}

void Power::setKiller() {
    killer = !killer;
}