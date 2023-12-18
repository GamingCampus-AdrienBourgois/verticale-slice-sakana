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
    ALGAE,
    TRASH2,
    TRASH1,
    CAN,
    WOOD,

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
    TEND
};

enum RectS {
    FRAME,
    REEND
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

        globalTexts.resize(TextS::TEND);
        globalRec.resize(RectS::REEND);
        



    }
    bool checkPixelCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
        sf::FloatRect intersection;
        if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds(), intersection)) {
            sf::IntRect rect1 = sprite1.getTextureRect();
            sf::IntRect rect2 = sprite2.getTextureRect();

            sf::Image image1 = sprite1.getTexture()->copyToImage();
            sf::Image image2 = sprite2.getTexture()->copyToImage();

            for (size_t i = intersection.left; i < intersection.left + intersection.width; ++i) {
                for (size_t j = intersection.top; j < intersection.top + intersection.height; ++j) {
                    
                    sf::Vector2f sprite1Pos = sprite1.getInverseTransform().transformPoint(static_cast<float>(i), static_cast<float>(j));
                    sf::Vector2f sprite2Pos = sprite2.getInverseTransform().transformPoint(static_cast<float>(i), static_cast<float>(j));

                    if (sprite1Pos.x > 0 && sprite1Pos.y > 0 && sprite1Pos.x < rect1.width && sprite1Pos.y < rect1.height &&
                        sprite2Pos.x > 0 && sprite2Pos.y > 0 && sprite2Pos.x < rect2.width && sprite2Pos.y < rect2.height) {

                        sf::Color color1 = image1.getPixel(static_cast<unsigned int>(sprite1Pos.x + rect1.left), static_cast<unsigned int>(sprite1Pos.y + rect1.top));
                        sf::Color color2 = image2.getPixel(static_cast<unsigned int>(sprite2Pos.x + rect2.left), static_cast<unsigned int>(sprite2Pos.y + rect2.top));

                        if (color1.a != 0 && color2.a != 0) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
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

    std::map<int, std::vector<sf::Sprite>> massSprt; // for mass generation
};