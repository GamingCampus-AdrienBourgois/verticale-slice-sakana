#include "Wall.hpp"

Wall::Wall(float x, float y) {
    _texture.loadFromFile("asset/wall.jpg");
    _sprite.setTexture(_texture);
    _sprite.setPosition(x, y);
}

void Wall::draw(Window_s& window) {
    window.addToRenderLayer(2, _sprite);
}

