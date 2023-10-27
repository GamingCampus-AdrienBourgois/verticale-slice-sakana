#pragma once
#include "Sprite.hpp"
#include "GameObject.hpp"

class Character : public Sprite_s {
public:
    Character(const std::string& filepath, float health, float speed);

    void TakeDamage(float damage);
    void Heal(float amount);
    void SetSpeed(float speed);
    float GetSpeed() const;

    bool IsAlive() const;
    float GetHealth() const;
    void Update(float deltaTime);


    void Shoot() {}
    void IncreaseScore(int value) {}
    int GetScore() const {}

private:
    float _health;
    float _speed;
};

