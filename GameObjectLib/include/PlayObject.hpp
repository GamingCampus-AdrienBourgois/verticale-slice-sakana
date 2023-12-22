#pragma once
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Music.hpp"
#include <map>
#include <iostream>

enum class Scene {
	SPRITESBG,
	RECTBG,
    SPRITESMASS,
	SPRITESGB,
	RECTGB,
	TEXTGB,
    FRONT,
    SEND
 
};

enum GlobalS {
    HOUSE,
    FISHERMANS,
    FISHERMANH,
    FISHERMANF,
    FISHERMAN,
    ALGAE,
    TRASH2,
    TRASH1,
    CAN,
    WOOD,
    HOOK,
    FISHERHOOK,
    HFISH,
    FISHA,
    FISHB,
    FISHC,
    FISHD,
    FISHE,
    FISHF,
    FISHG,
    FISHH,
    FISHI,
    GEND
};

enum FrontS {
    MAPGRAD,
    MAPBORDER,
    COVER,
    BLUR,
    
    FEND
};

enum BackS {
    MAP,
    SKY,
    WAVE,
    BEND
};

enum MassS {
    ALGAES,
    TRASHS1,
    TRASHS2,
    CANS,
    WOODS,
    WAVES,
    MEND
};

enum TextS {
    TIMER,
    FISHCNT,
    TEND
};

enum RectS {
    TRANS,
    FLASH,
    BAR,
    FRAME,
    FISHLINE,
    REEND
};

class PlayObject {
public:



    PlayObject();

    bool checkPixelCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
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

    std::map<int, std::vector<sf::Sprite>> massSprt; // for mass generation
};