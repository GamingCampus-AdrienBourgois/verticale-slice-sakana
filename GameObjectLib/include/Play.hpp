#pragma once
#include <SFML/Graphics.hpp>

#include "MenuObject.hpp"

class Play : public MenuObject {

public:
	Play();
	~Play() = default;

    void textureSetters(Window_s& window) {
        sf::Vector2u windowSize = window.getWindow().getSize();
        float X = static_cast<float>(windowSize.x);
        float Y = static_cast<float>(windowSize.y);

        // load texture and create de sprite 
        std::vector<std::string> globaleFile = { "asset\sprite\fishgame\map.png" };

        bgTex.resize(globaleFile.size());
        bgSprt.resize(globaleFile.size());

        for (size_t i = 0; i < globaleFile.size(); i++) {
            if (!bgTex[i].loadFromFile(globaleFile[i])) {
                throw std::runtime_error("Failed to load texture");
            }
            else {
                bgSprt[i].setTexture(bgTex[i]);
            }
        }
        // here we set scale/position/origin
        bgSprt[0].setScale(X / bgTex[0].getSize().x, Y / bgTex[0].getSize().y); // attapt pos to screen size

    }

    void load(Window_s& window) {
        std::vector<std::string> helpString = {
        };


        float spacing = 50;

        for (size_t i = 0; i < helpString.size(); ++i) {
            sf::Text helpText = createText(helpString[i], sf::Vector2f(window.getWindow().getSize().x / 2, 40 + (i * spacing)), 18, sf::Color(0, 0, 0));
            globalTexts.push_back(helpText);
        }

        textureSetters(window);
    }
};