#include "Character.hpp"

Character::Character(const std::string& texturePath) {
    _texture.loadFromFile(texturePath);
    _sprite.setTexture(_texture);
    _currentFrame = 0;
    _elapsedTime = 0.0f;
    _direction = 0;
    _animate = true;
}

void Character::update(float deltaTime) {
    if (_animate) {
        _elapsedTime += deltaTime;
        if (_elapsedTime >= FRAME_DURATION) {
            _currentFrame = (_currentFrame + 1) % ANIMATION_FRAMES;
            _elapsedTime -= FRAME_DURATION;
        }
        _sprite.setTextureRect(sf::IntRect(_currentFrame * FRAME_WIDTH, _direction * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
    }
}

void Character::stop() {
    _animate = false;
}

void Character::draw(Window_s& window) {
    window.addToRenderLayer(3, _sprite);
}

void Character::setPosition(float x, float y) {
    _sprite.setPosition(x, y);
}

sf::Vector2f Character::getPosition() const {
    return _sprite.getPosition();
}

void Character::setDirection(int dir) {
    _animate = true;
    _direction = dir;
}

void Character::setSize(float x, float y) {
    _sprite.setScale(x, y);
}