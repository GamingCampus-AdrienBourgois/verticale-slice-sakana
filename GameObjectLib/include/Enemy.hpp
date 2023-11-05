#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Node.hpp"
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
    void setOrigin(float x, float y) {
        _sprite.setOrigin(sf::Vector2f(x, y));
    }
    sf::Vector2f getPosition() const;
    void setDirection(int dir);
    void setSize(float x, float y);
    void move(const std::vector<std::vector<bool>> matrice, Character &hero, float deltaTime);
private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    int _currentFrame;
    float _elapsedTime;
    float _elapsed;
    int _direction;
    bool _animate;

    sf::Vector2i oldPos;
    sf::Vector2i oldTargetPos;

    std::vector<sf::Vector2i> path;

    Node node;

    static constexpr float FRAME_WIDTH = 89.1f;
    static const int FRAME_HEIGHT = 105;
    static const int ANIMATION_FRAMES = 6;
    static constexpr float FRAME_DURATION = 0.1f;

    static constexpr float SPEED = 100.0f;
};