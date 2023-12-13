#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include "Fish.hpp"


class Map {
	PlayObject& _obj;
    std::vector<Fish> fishs;

public:
	Map(PlayObject& obj) : _obj(obj) {

	}
    void textureSetters(Window_s& window) {
        sf::Vector2u windowSize = window.getWindow().getSize();
        float X = static_cast<float>(windowSize.x);
        float Y = static_cast<float>(windowSize.y);

        // load texture and create de sprite 
        std::vector<std::string> globaleFile = { "asset/sprite/fishgame/map.jpg", "asset/sprite/fishgame/map-cover.png" };

        _obj.bgTex.resize(globaleFile.size());
        _obj.bgSprt.resize(globaleFile.size());

        for (size_t i = 0; i < globaleFile.size(); i++) {
            if (!_obj.bgTex[i].loadFromFile(globaleFile[i]) ) {
                throw std::runtime_error("Failed to load texture");
            }
            else {
                _obj.bgSprt[i].setTexture(_obj.bgTex[i]);
            }
        }

        float scaleX = X / _obj.bgTex[BackS::MAP].getSize().x; // scale to screen level x
        float scaleY = Y / _obj.bgTex[BackS::MAP].getSize().y; // scale to screen level y
        _obj.bgSprt[0].setScale(scaleX * 10, scaleY * 10);

        float scaleX1 = scaleX * (_obj.bgTex[BackS::MAP].getSize().x / static_cast<float>(_obj.bgTex[BackS::MAPGRAD].getSize().x)); // scale to map x
        float scaleY1 = scaleY * (_obj.bgTex[BackS::MAP].getSize().y / static_cast<float>(_obj.bgTex[BackS::MAPGRAD].getSize().y)); // scale to map y
        _obj.bgSprt[1].setScale(scaleX1 * 10, scaleY1 * 10);
        
        // Create the fish
        fishs = Fish::generateFishes("Save/saveFish.txt");
        int j = 0;

        _obj.globalSprt.resize(_obj.globalSprt.size() + fishs.size());

        std::cout << _obj.globalSprt.size();


        std::cout << _obj.globalSprt.size();

        
    }


    void load(Window_s& window) {
        textureSetters(window);

    }

};