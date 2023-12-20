#pragma once
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Music.hpp"

enum class Scene {
	SPRITESBG,
	RECTBG,
	SPRITESGB,
	RECTGB,
	TEXTGB,
    FRONT,
    SEND
 
};

enum GlobalS {
    HOOK,
    HOUSE,
    FISHERMAN,
    FISHERMAND,
    FISHERMANS,
    HFISH,
    FISHA,
    FISHB,
    FISHC,
    FISHD,
    GEND
};

enum FrontS {
    MAPBORDER,
    MAPGRAD,
    FEND
};

enum BackS {
    MAP,
    SKY,
    BEND
};

enum RectangleS {
    BAR,
    TRANS,
    REND
};

class PlayObject {
public:



    PlayObject() {
        globalSprt.resize(GlobalS::GEND);
        globalTex.resize(GlobalS::GEND);
        bgSprt.resize(BackS::BEND);
        bgTex.resize(BackS::BEND);
        frontTex.resize(FrontS::FEND);
        frontSprt.resize(FrontS::FEND);
        globalRec.resize(RectangleS::REND);
    }
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

    std::vector<sf::Texture> frontTex; // texture for front sprites
    std::vector<sf::Sprite> frontSprt; // sprites for front (second plan)

};