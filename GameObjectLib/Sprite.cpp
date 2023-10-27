#include "Sprite.hpp"

Sprite_s::Sprite_s(const std::string& filepath) : _filepath(filepath), _sprite(), _currentFrame(0), _frameDuration(0.1f) {
    if (_texture.loadFromFile(_filepath)) {
        _sprite.setTexture(_texture);
        _hitbox.setSize(GetSize());
    }
    else {
        std::cout << "Error loading texture" << std::endl;
    }
}

Sprite_s::~Sprite_s() = default;

void Sprite_s::AddAnimationFrame(const sf::IntRect& rect) {
    _frames.push_back(rect);
    if (_frames.size() == 1) {
        _sprite.setTextureRect(_frames[0]);
    }
}

void Sprite_s::UpdateAnimation() {
    float time = _frameClock.getElapsedTime().asSeconds();
    if (time >= _frameDuration) {
        _currentFrame = (_currentFrame + 1) % _frames.size();
        _sprite.setTextureRect(_frames[_currentFrame]);
        _frameClock.restart();
    }
}

void Sprite_s::SetFrameDuration(float duration) {
    _frameDuration = duration;
}

bool Sprite_s::Intersects(const Sprite_s& other) const {
    return _hitbox.getGlobalBounds().intersects(other._hitbox.getGlobalBounds());
}

sf::Sprite& Sprite_s::GetSprite() {
    return _sprite;
}

void Sprite_s::SetOrigin(float x, float y) {
    _sprite.setOrigin(x, y);
}

void Sprite_s::SetPosition(float x, float y) {
    _sprite.setPosition(x, y);
    _hitbox.setPosition(x, y);
}

void Sprite_s::SetRotation(float angle) {
    _sprite.setRotation(angle);
}

void Sprite_s::Rotate(float angle) {
    _sprite.rotate(angle);
}

void Sprite_s::SetScale(float scaleX, float scaleY) {
    _sprite.setScale(scaleX, scaleY);
}

void Sprite_s::Move(float offsetX, float offsetY) {
    _sprite.move(offsetX, offsetY);
    _hitbox.move(offsetX, offsetY);
}

sf::Vector2f Sprite_s::GetOrigin() const {
    return _sprite.getOrigin();
}

sf::Vector2f Sprite_s::GetPosition() const {
    return _sprite.getPosition();
}

float Sprite_s::GetRotation() const {
    return _sprite.getRotation();
}

sf::Vector2f Sprite_s::GetScale() const {
    return _sprite.getScale();
}

sf::Vector2f Sprite_s::GetSize() const {
    return sf::Vector2f(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
}

void Sprite_s::SetHitbox(float width, float height) {
    _hitbox.setSize(sf::Vector2f(width, height));
    _hitbox.setOrigin(width / 2, height / 2);
}


