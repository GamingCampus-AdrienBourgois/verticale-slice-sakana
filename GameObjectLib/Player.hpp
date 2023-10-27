#pragma once
#include "Character.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"

class Player : public Sprite_s {
public:
    Player(const std::string& filepath, float health, float speed);

    void Shoot();
    void IncreaseScore(int value);
    int GetScore() const;

    void TakeDamage(float damage);




private:
    int _score;
};
