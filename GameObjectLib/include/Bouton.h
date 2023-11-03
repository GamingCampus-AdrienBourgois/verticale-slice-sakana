#pragma 

#include"SFML/Graphics.hpp"

class Bouton {
    //sf::RectangleShape* cadre;
    sf::Font font;
    sf::Text* textBouton;
    std::string intitule;
    bool click;

public:
    Bouton() = default;

    Bouton(std::string etiquette, float x = 0.f, float y = 0.f);
    ~Bouton();

    void drawBouton(sf::RenderWindow* w);

    void assignAction(void* f);

    void onClick(sf::Mouse* m, sf::RenderWindow* f);

    void setPosition(float x, float y);

    void setPosition(sf::Vector2f p);

    void setThickness(float t);

    void setColorBouton(sf::Color c);

    void setColorTextBouton(sf::Color c);
	
};