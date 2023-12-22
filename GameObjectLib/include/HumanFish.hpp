#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"

#include <iostream>

class HumanFish {
    PlayObject& _obj;

    // cam
    sf::View& cameraView;
    float zoomFactor;
    float camDelay;

    // animation
    float elapsed;
    int currentFrame;
    bool cloak;
    bool cloaked;

    // move
    sf::Vector2f targetPosition;
    float speed;
    bool isPushing;
    float pushElapsed;
    float pushDelay;

    // change size
    float elapsedSize;

    // shader
    sf::Shader Rshader;
    float radius;
    bool shaderLoaded;
    sf::RenderStates shaderStates;

    static constexpr float FRAME_WIDTH = 29.f;
    static constexpr float FRAME_HEIGHT = 21.f;
    static constexpr float M_PI = 3.1416f;

public:
    HumanFish(PlayObject& obj, sf::View& _cameraView);

    void load(Window_s& window);
    void textureSetters(Window_s& window);
    void handleEvent(const sf::Event& event, Window_s& window);
    void updateCamera(float deltaTime, Window_s& window);
    bool isNotDead();
    void followMouse(Window_s& window, float deltaTime);
    void pusher(Window_s& window, float deltaTime, bool isPush);
    void setSpeed(float _speed);
    void animate(float deltaTime, Window_s& window);
    void handleObstacleCollision(Window_s& window, MassS type);
    void handleFishsCollision(Window_s& window);
    void checkAndEatAlgae(Window_s& window);
    void shrinkWithTime(float deltaTime);
    void killer(Window_s& window);
    void applyAuraEffect(Window_s& window);
    void setCloack();
    const bool getCloak() const;
};
