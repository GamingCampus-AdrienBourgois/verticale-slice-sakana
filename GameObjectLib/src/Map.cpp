#include "Map.hpp"

Map::Map(PlayObject& obj) : _obj(obj) {
    frame = 0;
    elapsed = 0.f;
}
void Map::textureSetters(Window_s& window) {
    sf::Vector2u windowSize = window.getWindow().getSize();
    float X = static_cast<float>(windowSize.x);
    float Y = static_cast<float>(windowSize.y);
    float mult = 20.f;


    // load texture and create de sprite 
    std::vector<std::string> globaleFile = { "asset/sprite/fishgame/map.jpg", "asset/sprite/fishgame/sky.png" };
    std::vector<std::string> frontFile = { "asset/sprite/fishgame/map-cover.png",  "asset/sprite/fishgame/borderN.png", "asset/sprite/fishgame/cover.png" };



    for (size_t i = 0; i < globaleFile.size(); i++) {
        if (!_obj.bgTex[i].loadFromFile(globaleFile[i])) {
            throw std::runtime_error("Failed to load texture");
        }
        else {
            _obj.bgSprt[i].setTexture(_obj.bgTex[i]);
        }
    }
    for (size_t i = 0; i < frontFile.size(); i++) {
        if (!_obj.frontTex[i].loadFromFile(frontFile[i])) {
            throw std::runtime_error("Failed to load texture");
        }
        else {
            _obj.frontSprt[i].setTexture(_obj.frontTex[i]);
        }
    }
    if (!_obj.bgTex[BackS::WAVE].loadFromFile("asset/sprite/fishgame/Waves.png")) {
        throw std::runtime_error("Failed to load texture");
    }




    // map
    float scaleX = X / _obj.bgTex[BackS::MAP].getSize().x; // scale to screen level x
    float scaleY = Y / _obj.bgTex[BackS::MAP].getSize().y; // scale to screen level y
    _obj.bgSprt[BackS::MAP].setScale(scaleX * mult, scaleY * mult);


    // map grad
    float scaleX1 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.frontTex[FrontS::MAPGRAD].getSize().x)); // scale to map x
    float scaleY1 = scaleY * (_obj.bgTex[BackS::MAP].getSize().y / static_cast<float>(_obj.frontTex[FrontS::MAPGRAD].getSize().y)); // scale to map y
    _obj.frontSprt[FrontS::MAPGRAD].setScale(scaleX1 * mult, scaleY1 * mult);

    // map border
    float scaleX2 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.frontTex[FrontS::MAPBORDER].getSize().x)); // scale to map x
    float scaleY2 = scaleY * (_obj.bgTex[BackS::MAP].getSize().y / static_cast<float>(_obj.frontTex[FrontS::MAPBORDER].getSize().y)); // scale to map y
    _obj.frontSprt[FrontS::MAPBORDER].setScale(scaleX2 * mult, scaleY2 * mult);

    // sky
    float scaleX3 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.bgTex[BackS::SKY].getSize().x)); // scale to map x
    float scaleY3 = 1.f;
    _obj.bgSprt[BackS::SKY].setScale(scaleX3 * mult, scaleY3 * 3.f);
    _obj.bgSprt[BackS::SKY].setPosition(sf::Vector2f(0, -1.f * (static_cast<float>(_obj.bgTex[BackS::SKY].getSize().y) * 3.f)));

    float scaleX5 = 2.f;
    float scaleY5 = 10000.f;
    _obj.frontSprt[FrontS::COVER].setScale(scaleX5, scaleY5);
    _obj.frontSprt[FrontS::COVER].setPosition(sf::Vector2f(_obj.bgSprt[BackS::MAP].getScale().x * _obj.bgTex[BackS::MAP].getSize().x, 0 + _obj.bgSprt[BackS::SKY].getPosition().y));

    // waves
    float waveSectionWidth = static_cast<float>(_obj.bgTex[BackS::WAVE].getSize().x) / 4.f;
    float scaleX4 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.bgTex[BackS::WAVE].getSize().x));
    float scaleY4 = 1;
    int totalWaveSections = static_cast<int>(std::ceil(static_cast<float>(_obj.bgTex[BackS::MAP].getSize().x * _obj.bgSprt[BackS::MAP].getScale().x) / waveSectionWidth));
    for (int i = 0; i < totalWaveSections + 1; ++i) {
        sf::Sprite wave;
        wave.setTexture(_obj.bgTex[BackS::WAVE]);
        wave.setPosition(sf::Vector2f((i * waveSectionWidth) - 68 - (i * 128), -1.f * (static_cast<float>(_obj.bgTex[BackS::WAVE].getSize().y))));
        _obj.massSprt[MassS::WAVES].push_back(wave);
    }



}



void Map::load(Window_s& window) {
    textureSetters(window);

}

void Map::animation(float deltaTime) {
    elapsed += deltaTime;

    if (elapsed >= 0.1f) {
        float width = static_cast<float>(_obj.bgTex[BackS::WAVE].getSize().x) / 4.f;
        float height = static_cast<float>(_obj.bgTex[BackS::WAVE].getSize().y);

        frame = (frame + 1) % 4;

        for (auto& wave : _obj.massSprt[MassS::WAVES]) {
            wave.setTextureRect(sf::IntRect(static_cast<int>(width) * frame, 0, static_cast<int>(width), static_cast<int>(height)));
        }

        elapsed -= 0.1f;
    }
}