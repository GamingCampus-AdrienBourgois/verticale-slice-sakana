#include "Path.hpp"


Path::Path(float x, float y) {
    _texture.loadFromFile("asset/path.jpg");
    _sprite.setTexture(_texture);
    _sprite.setPosition(x, y);
}

void Path::draw(Window_s& window) {
    window.addToRenderLayer(1, _sprite);
}