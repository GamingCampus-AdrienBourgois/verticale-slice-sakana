#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "GameObject.hpp"
#include "Character.hpp"
#include <vector>
class Window_s;

class Enemy : public GameObject {
public:
    Enemy(const std::string& texturePath);

    void update(float deltaTime);
    void stop();
    void draw(Window_s& window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void setDirection(int dir);
    void setSize(float x, float y);
    void move(const std::vector<std::vector<bool>> matrice, Character &hero);
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    int _currentFrame;
    float _elapsedTime;
    int _direction;
    bool _animate;

    static constexpr float FRAME_WIDTH = 89.1f;
    static const int FRAME_HEIGHT = 105;
    static const int ANIMATION_FRAMES = 6;
    static constexpr float FRAME_DURATION = 0.1f;
};