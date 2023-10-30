#pragma once
#include "GameObject.hpp"

class Wall : public GameObject {
public:
    Wall(float x, float y);
    void draw(Window_s &window);

    static constexpr float SIZE = 2.5f;
    static const int WIDTH = 100;
    static const int HEIGHT = 100;

    sf::FloatRect getBounds() const {
        return _sprite.getGlobalBounds();
    }

private:

    sf::Sprite _sprite;
    sf::Texture _texture;






};