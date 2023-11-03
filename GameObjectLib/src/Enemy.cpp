#include "Enemy.hpp"

Enemy::Enemy(const std::string& texturePath) : node(sf::Vector2i(0, 0)) {
    _texture.loadFromFile(texturePath);
    _sprite.setTexture(_texture);
    sf::Vector2u textureSize = _sprite.getTexture()->getSize();
    //_sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
    _currentFrame = 0;
    _elapsedTime = 0.0f;
    _elapsed = 0.0f;
    _direction = 0;
    _animate = true;

}

void Enemy::update(float deltaTime) {
    if (_animate) {
        _elapsedTime += deltaTime;
        if (_elapsedTime >= FRAME_DURATION) {
            _currentFrame = (_currentFrame + 1) % ANIMATION_FRAMES;
            _elapsedTime -= FRAME_DURATION;
        }
        _sprite.setTextureRect(sf::IntRect(_currentFrame * FRAME_WIDTH, _direction * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
    }
}

void Enemy::stop() {
    _animate = false;
}

void Enemy::draw(Window_s& window) {
    window.addToRenderLayer(4, _sprite);
}

void Enemy::setPosition(float x, float y) {
    _sprite.setPosition(x, y);
}

sf::Vector2f Enemy::getPosition() const {
    return _sprite.getPosition();
}

void Enemy::setDirection(int dir) {
    _animate = true;
    _direction = dir;
}

void Enemy::setSize(float x, float y) {
    _sprite.setScale(x, y);
}

#include <iostream>

void Enemy::move(const std::vector<std::vector<bool>> matrice, Character &hero, float deltaTime)
{
    sf::Vector2f heroPosition = hero.getPosition();
    sf::Vector2f enemyPosition = _sprite.getPosition();
    sf::Vector2i Position;
    sf::Vector2i TargetPosition;

    TargetPosition.x = static_cast<int>(heroPosition.x / (Wall::WIDTH * Wall::SIZE));
    TargetPosition.y = static_cast<int>(heroPosition.y / (Wall::HEIGHT * Wall::SIZE));

    Position.x = static_cast<int>(enemyPosition.x / (Wall::WIDTH * Wall::SIZE));
    Position.y = static_cast<int>(enemyPosition.y / (Wall::HEIGHT * Wall::SIZE));


    std::vector<sf::Vector2i> path = node.findPath(matrice, Position, TargetPosition);



    for (auto it = path.begin(); it != path.end(); ++it) {
        std::cout << "X: " << it->x << ", Y: " << it->y << std::endl;
    }
    std::cout << "///////" << std::endl;

    //std::cout << TargetPosition.x << " - " << TargetPosition.y << std::endl;
    // Move the enemy along the path

    _elapsed += deltaTime;
    if (_elapsed >= 0.5f) {


        if (!path.empty() && path.size() > 1) {
            // For simplicity, moving to the next position on the path
            _sprite.setPosition(path[1].x * Wall::WIDTH * Wall::SIZE, path[1].y * Wall::HEIGHT * Wall::SIZE);
        }
        _elapsed -= 0.5f;
    }
}