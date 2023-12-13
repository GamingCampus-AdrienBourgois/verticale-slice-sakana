#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include "Fish.hpp"


class Map {
	PlayObject& _obj;


public:
	Map(PlayObject& obj) : _obj(obj) {

	}
    void textureSetters(Window_s& window) {
        sf::Vector2u windowSize = window.getWindow().getSize();

        float X = static_cast<float>(windowSize.x);
        float Y = static_cast<float>(windowSize.y);

        // load texture and create de sprite 
        std::vector<std::string> globaleFile = { "asset/sprite/fishgame/map.jpg"};
        std::vector<std::string> frontFile = { "asset/sprite/fishgame/map-cover.png",  "asset/sprite/fishgame/border.png" };


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

        

        float scaleX = X / _obj.bgTex[BackS::MAP].getSize().x; // scale to screen level x
        float scaleY = Y / _obj.bgTex[BackS::MAP].getSize().y; // scale to screen level y
        _obj.bgSprt[BackS::MAP].setScale(scaleX * 10, scaleY * 10);

        float scaleX1 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.frontTex[FrontS::MAPGRAD].getSize().x)); // scale to map x
        float scaleY1 = scaleY * (_obj.bgTex[BackS::MAP].getSize().y / static_cast<float>(_obj.frontTex[FrontS::MAPGRAD].getSize().y)); // scale to map y
        _obj.frontSprt[FrontS::MAPGRAD].setScale(scaleX1 * 10, scaleY1 * 10);
        
        float scaleX2 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.frontTex[FrontS::MAPBORDER].getSize().x)); // scale to map x
        float scaleY2 = scaleY * (_obj.bgTex[BackS::MAP].getSize().y / static_cast<float>(_obj.frontTex[FrontS::MAPBORDER].getSize().y)); // scale to map y
        _obj.frontSprt[FrontS::MAPBORDER].setScale(scaleX2 * 10, scaleY2 * 10);
        
    }


    void load(Window_s& window) {
        textureSetters(window);

    }

};