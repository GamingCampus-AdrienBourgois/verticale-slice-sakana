#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include "Fish.hpp"


class Map {
	PlayObject& _obj;

    int frame;
    float elapsed;
public:
	Map(PlayObject& obj) : _obj(obj) {
        frame = 0;
        elapsed = 0.f;
	}
    void textureSetters(Window_s& window) {
        sf::Vector2u windowSize = window.getWindow().getSize();

        float X = static_cast<float>(windowSize.x);
        float Y = static_cast<float>(windowSize.y);

        // load texture and create de sprite 
        std::vector<std::string> globaleFile = { "asset/sprite/fishgame/map.jpg", "asset/sprite/fishgame/sky.png",  "asset/sprite/fishgame/Waves.png" };
        std::vector<std::string> frontFile = { "asset/sprite/fishgame/map-cover.png",  "asset/sprite/fishgame/borderN.png" };



        for (size_t i = 0; i < globaleFile.size(); i++) {
            if (!_obj.bgTex[i].loadFromFile(globaleFile[i]) ) {
                throw std::runtime_error("Failed to load texture");
            }
            else {
                _obj.bgSprt[i].setTexture(_obj.bgTex[i]);
            }
        }
        for (size_t i = 0; i < frontFile.size(); i++) {
            if (!_obj.frontTex[i].loadFromFile(frontFile[i]) ) {
                throw std::runtime_error("Failed to load texture");
            }
            else {
                _obj.frontSprt[i].setTexture(_obj.frontTex[i]);
            }
        }

        float mult = 20.f;

        float scaleX = X / _obj.bgTex[BackS::MAP].getSize().x; // scale to screen level x
        float scaleY = Y / _obj.bgTex[BackS::MAP].getSize().y; // scale to screen level y
        _obj.bgSprt[BackS::MAP].setScale(scaleX * mult, scaleY * mult);

        /*
        float scaleX1 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.frontTex[FrontS::MAPGRAD].getSize().x)); // scale to map x
        float scaleY1 = scaleY * (_obj.bgTex[BackS::MAP].getSize().y / static_cast<float>(_obj.frontTex[FrontS::MAPGRAD].getSize().y)); // scale to map y
        _obj.frontSprt[FrontS::MAPGRAD].setScale(scaleX1 * mult, scaleY1 * mult);*/
        
        float scaleX2 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.frontTex[FrontS::MAPBORDER].getSize().x)); // scale to map x
        float scaleY2 = scaleY * (_obj.bgTex[BackS::MAP].getSize().y / static_cast<float>(_obj.frontTex[FrontS::MAPBORDER].getSize().y)); // scale to map y
        _obj.frontSprt[FrontS::MAPBORDER].setScale(scaleX2 * mult, scaleY2 * mult);
        
        float scaleX3 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.bgTex[BackS::SKY].getSize().x)); // scale to map x
        float scaleY3 = 1;
        _obj.bgSprt[BackS::SKY].setScale(scaleX3 * mult, scaleY3 * 3.f);
        _obj.bgSprt[BackS::SKY].setPosition(sf::Vector2f(0, -1.f * (static_cast<float>(_obj.bgTex[BackS::SKY].getSize().y) * 3.f)));

        float scaleX4 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.bgTex[BackS::WAVE].getSize().x));
        float scaleY4 = 1;
        _obj.bgSprt[BackS::WAVE].setPosition(sf::Vector2f(0, -1.f * (static_cast<float>(_obj.bgTex[BackS::WAVE].getSize().y))));
    }


    void load(Window_s& window) {
        textureSetters(window);

    }

    void animation(float deltaTime) {
        elapsed += deltaTime;

        if (elapsed >= 0.1f) {
            float width = _obj.bgTex[BackS::WAVE].getSize().x / 4.f;
            float height = _obj.bgTex[BackS::WAVE].getSize().y;

            frame = (frame + 1) % 4;
            _obj.bgSprt[BackS::WAVE].setTextureRect(sf::IntRect(width * frame, 0, width, height));

            elapsed -= 0.1f;
        }
    }

};