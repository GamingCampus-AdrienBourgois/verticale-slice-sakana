#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "GameObject.hpp"

class Sprite_s : public GameObject {
public:
    Sprite_s(const std::string& filepath);
    ~Sprite_s();

    void AddAnimationFrame(const sf::IntRect& rect);
    void UpdateAnimation();
    void SetFrameDuration(float duration);
    bool Intersects(const Sprite_s& other) const;

    sf::Sprite& GetSprite();
    void SetOrigin(float x, float y);
    void SetPosition(float x, float y);
    void SetRotation(float angle);
    void SetHitbox(float width, float height);
    void Rotate(float angle);
    void SetScale(float scaleX, float scaleY);
    void Move(float offsetX, float offsetY);

    sf::Vector2f GetOrigin() const;
    sf::Vector2f GetPosition() const;
    float GetRotation() const;
    sf::Vector2f GetScale() const;
    sf::Vector2f GetSize() const;

private:
    std::string _filepath;
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::RectangleShape _hitbox; // Pour la détection de collision

    std::vector<sf::IntRect> _frames; // Pour la gestion des animations
    int _currentFrame;
    sf::Clock _frameClock;
    float _frameDuration;
};
