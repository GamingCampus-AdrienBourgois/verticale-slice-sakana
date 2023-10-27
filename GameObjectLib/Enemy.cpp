#include "Enemy.hpp"
#include "Player.hpp"
#include <cmath>

Enemy::Enemy(const std::string& filepath, float health, float speed, float detectionRange)
    : Character(filepath, health, speed), _detectionRange(detectionRange), _target(nullptr) 
{

}

void Enemy::SetTarget(Player* target) {
    _target = target;
}

void Enemy::Chase(float deltaTime) {
    if (!_target) return;

    sf::Vector2f direction = _target->GetPosition() - GetPosition();
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude <= _detectionRange) {
        direction.x /= magnitude;
        direction.y /= magnitude;

        Move(direction.x * GetSpeed() * deltaTime, direction.y * GetSpeed() * deltaTime);
    }
}

void Enemy::Shoot() {
    if (!_target) return;

    sf::Vector2f distance = _target->GetPosition() - GetPosition();
    float magnitude = std::sqrt(distance.x * distance.x + distance.y * distance.y);

    if (magnitude <= 50.0f) {
        _target->TakeDamage(10.0f);
    }
}

float Enemy::GetDetectionRange() const {
    return _detectionRange;
}

