#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>

#include "Window.hpp"

class Window_s; // D�claration anticip�e

enum class Layer {
    SRITESBG = 1,
    MENUBUTTON,
    TEXTBUTTON,
    PARTICLES,
    BAR, // for slider
    HANDLE, // for slider
    TEXTSLIDER, // for slider
    TEXTRANDOM,
    SPRITESGB

};
// 1 sprites for background (be rendered first)
// 2 menu buttons (destroyed after switch betwin states)
// 3 text for buttons (destroyed after switch betwin states)
// 4 particles (like rain or wind or frame)
// 5 bar for settings slider (destroyed after switch betwin states)
// 6 handle for settings slider (destroyed after switch betwin states)
// 7 text for bar for settings slider (destroyed after switch betwin states)
// 8 random text in menu (destroyed after switch betwin states)
// 9 global sprites for what ever (will be rendered first)


// Classe de base abstraite pour les objets de menu et ces differents states
class MenuObject {
public:
    virtual ~MenuObject() = default;

    virtual void draw(Window_s& window);
    virtual void resetValues(Window_s& window);
    virtual sf::Text setTextOnButton(const std::string& text, sf::RectangleShape& button, unsigned int size, sf::Color color);
    virtual void changeOnMouse(Window_s& window);
    virtual sf::Text createText(const std::string& text, const sf::Vector2f& position, unsigned int size, sf::Color color);
    virtual void reloding(Window_s& window);

    virtual void load(Window_s& window) = 0;

    enum MenuStates 
    {
        BASE,
        PLAY,
        SETTINGS,
        HELP,
        SUCCESS,
        CREDIT,
        QUIT
    };
    enum MusicStates
    {
        MBASE,
        MCREDIT,
        MSETTINGS,
        MHELP,
        MSUCCESS
    };

protected:
    sf::Font _fontButton;
    sf::Font _fontAny;

    std::vector<sf::Text> buttonTexts; // texts on the buttons
    std::vector<sf::Texture> buttonTex; // texture for buttons (esthetic)
    std::vector<sf::RectangleShape> buttons; // buttons for each states

    std::vector<sf::RectangleShape> particles; // rectangle shape for esthetisme like rain or frame

    std::vector<sf::Texture> globalTex; // texture for all the sprites
    std::vector<sf::Sprite> globalSprt; // sprites for anything (first plan)
    std::vector<sf::Text> globalTexts; // texts for anything


    std::vector<sf::Sprite> bgSprt; // sprites for background (second plan)
    std::vector<sf::Texture> bgTex; // texture for background
};
