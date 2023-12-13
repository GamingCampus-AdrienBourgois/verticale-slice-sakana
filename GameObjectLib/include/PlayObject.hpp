#pragma once
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Music.hpp"

enum class Scene {
	SPRITESBG = 1,
	RECTBG,
	SPRITESGB,
	RECTGB,
	TEXTGB
};

enum GlobalS {
    HFISH,
    FISHA,
    FISHB,
    FISHC,
    FISHD,
    FISHE,
    FISHF
};

enum BackS {
    MAP,
    MAPGRAD
};

class PlayObject {
public:



    PlayObject() = default;
    virtual ~PlayObject() = default;

    sf::Text createText(const std::string& text, const sf::Vector2f& position, unsigned int size, sf::Color color);

    void draw(Window_s& window);
    void resetValues(Window_s& window);


    // public because PlayObject is the object
    sf::Font _fontAny; // font for anything

    std::vector<sf::RectangleShape> globalRec; // rectangle shape for anything
    std::vector<sf::Texture> globalTex; // texture for all the sprites
    std::vector<sf::Sprite> globalSprt; // sprites for anything (first plan)
    std::vector<sf::Text> globalTexts; // texts for anything

    std::vector<sf::Texture> bgTex; // texture for background sprites
    std::vector<sf::Sprite> bgSprt; // sprites for background (second plan)
    std::vector<sf::RectangleShape> bgRec; // rectangle shape for any background effect like rain



};