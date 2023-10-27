#pragma once

#include <SFML/Graphics.hpp>


class GameObject {
public:
    GameObject() = default;

    virtual ~GameObject() = default;


    virtual void Shoot() = 0;
    virtual void IncreaseScore(int value) = 0;
    virtual int GetScore() const = 0;

    virtual void TakeDamage(float damage) = 0;

private:
    sf::Vector2f position;
    float rotation;
};
