#include "Path.hpp"


Path::Path(float x, float y) {
    _texture.loadFromFile("asset/path.jpg");
    _sprite.setTexture(_texture);
    _sprite.setPosition(x * SIZE, y * SIZE);
    _sprite.setScale(SIZE, SIZE);
}

void Path::draw(Window_s& window) {
    window.addToRenderLayer(1, _sprite);
}