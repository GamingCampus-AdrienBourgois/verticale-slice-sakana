#include "Character.hpp"

Character::Character(const std::string& filepath, float health, float speed)
    : Sprite_s(filepath), _health(health), _speed(speed) {}

void Character::TakeDamage(float damage) {
    _health -= damage;
    if (_health < 0.0f) {
        _health = 0.0f;
    }
}

void Character::Heal(float amount) {
    _health += amount;

}

void Character::SetSpeed(float speed) {
    _speed = speed;
}

float Character::GetSpeed() const {
    return _speed;
}

bool Character::IsAlive() const {
    return _health > 0.0f;
}

float Character::GetHealth() const {
    return _health;
}

void Character::Update(float deltaTime) {

    Sprite_s::UpdateAnimation();

}
