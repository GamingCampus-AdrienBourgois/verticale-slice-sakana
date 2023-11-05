#pragma once
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include "Labyrinth.hpp"

class Character : public GameObject {
public:
    enum Directions
    {
        UP,
        LEFT,
        DOWN,
        RIGHT,
    };

    Character(const std::string& texturePath);

    virtual void draw(Window_s& window) override;
    virtual void update(float deltaTime) override;
    void stop();

    virtual void setPosition(float x, float y) override;
    void setDirection(Directions direction);
    virtual void setSize(float x, float y) override;
    sf::Vector2f getPosition() const;


    sf::FloatRect getFeetBoundsAtPosition(float x, float y) const;
    void move(float deltaTime, const Labyrinth& labyrinth);

    bool offGrid(Labyrinth& labyrinth);





private:
    //sf::RectangleShape _hitboxRect; for hitbox checks

    //sf::Vector2f _movementDirection;


    // Animation
    static constexpr float FRAME_WIDTH = 63.6f;
    static const int FRAME_HEIGHT = 61;
    static const int ANIMATION_FRAMES = 9;
    static constexpr float FRAME_DURATION = 0.1f;

    // Speed
    static constexpr float SPEED = 500.0f;

    sf::Texture _texture;
    sf::Sprite _sprite;

    int _currentFrame;
    float _elapsedTime;
    Directions _direction;

    bool _animate;



};
