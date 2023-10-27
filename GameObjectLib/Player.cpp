#include "Player.hpp"
#include "Character.hpp"

Player::Player(const std::string& filepath, float health, float speed)
    : Character(filepath, health, speed), _score(0) {}

void Player::Shoot() {
    // logique
}

void Player::IncreaseScore(int value) {
    _score += value;
}

int Player::GetScore() const {
    return _score;
}

void Player::TakeDamage(float damage) {
    Character::TakeDamage(damage);
}
