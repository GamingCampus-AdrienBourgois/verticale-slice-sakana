#pragma once
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class Character : public GameObject {
public:
    Character(const std::string& texturePath);

    virtual void draw(Window_s& window) override;
    virtual void update(float deltaTime) override;
    void stop();

    virtual void setPosition(float x, float y) override;
    virtual void setDirection(int dir) override;
    virtual void setSize(float x, float y) override;
    sf::Vector2f getPosition() const;


    sf::FloatRect getFeetBoundsAtPosition(float x, float y) const {
        sf::FloatRect globalBounds = _sprite.getGlobalBounds();


        float feetHeight = globalBounds.height * 0.25f; 

        // Réduire la largeur de la hitbox par un certain pourcentage
        float adjustedWidth = globalBounds.width * 0.30f;
        float widthOffset = (globalBounds.width - adjustedWidth) / 2;

        widthOffset -= globalBounds.width * 0.15f;

        float heightOffset = globalBounds.height * 0.1f;
        return sf::FloatRect(x + widthOffset, y + globalBounds.height - feetHeight - heightOffset, adjustedWidth, feetHeight);

    }





    static constexpr float FRAME_WIDTH = 63.6f;
    static const int FRAME_HEIGHT = 61;
    static const int ANIMATION_FRAMES = 9;
    static constexpr float FRAME_DURATION = 0.1f;

private:
    sf::Texture _texture;
    sf::Sprite _sprite;


    int _currentFrame;
    float _elapsedTime;
    int _direction;

    bool _animate;

};
