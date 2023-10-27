#pragma once
#include "Character.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"

class Player;

class Enemy : public Sprite_s {
public:
    Enemy(const std::string& filepath, float health, float speed, float detectionRange);

    void SetTarget(Player* target);
    void Chase(float deltaTime);


    float GetDetectionRange() const;

    void Shoot();
    void IncreaseScore(int value) {}
    int GetScore() const {}
    void TakeDamage(float damage) {}
private:
    Player* _target;  // Pointeur vers le joueur pour la poursuite
    float _detectionRange;
};