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
// 1 menu buttons (destroyed after switch betwin states)
// 2 text for buttons (destroyed after switch betwin states)
// 3 bar for settings slider (destroyed after switch betwin states)
// 4 handle for settings slider (destroyed after switch betwin states)
// 5 text for bar for settings slider (destroyed after switch betwin states)
// 6 random text in menu (destroyed after switch betwin states)


// Classe de base abstraite pour les objets de menu
// Elle sert pour la creation des boutons avec draw et setTextOnButton ainsi que la reinitialisation des �tats avec resetValues
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
    };

protected:
    sf::Font _fontButton;
    sf::Font _fontAny;

    unsigned int buttonCount;
    std::vector<sf::Text> buttonTexts; // texts on the buttons
    std::vector<sf::Texture> buttonTex; // texture for buttons (esthetic)
    std::vector<sf::RectangleShape> buttons; // buttons for each states

    std::vector<sf::Text> basicTexts; // texts for anything

    std::vector<sf::RectangleShape> particles;

    std::vector<sf::Texture> globalTex;
    std::vector<sf::Sprite> globalSprt;

    std::vector<sf::Texture> bgTex;
    std::vector<sf::Sprite> bgSprt;
};
