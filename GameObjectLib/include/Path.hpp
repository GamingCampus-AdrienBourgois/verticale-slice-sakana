#pragma once
#include "GameObject.hpp"

class Path : public GameObject {
public:
    Path(float x, float y);
    void draw(Window_s &window);

    static constexpr float SIZE = 2.5f;
    static const int WIDTH = 100;
    static const int HEIGHT = 100;
private:


    sf::Sprite _sprite;
    sf::Texture _texture;


};