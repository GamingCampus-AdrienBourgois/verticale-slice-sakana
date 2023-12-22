#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include <string>
#include <vector>
#include <iostream>
#include "HumanFish.hpp"

class Fish {
    std::string name;
    float speed;
    float scale;
    std::string power;
    std::string path;

    float focus;

    std::vector<float> timeSinceLastDirectionChange;
    std::vector<bool> colidedVec;
    std::vector<float> depthVec;

    int currentFrame;
    float elapsed;

    std::map<size_t, std::vector<sf::Vector2i>> nonVoidPixelCoordinatesMap;

public:
    Fish();
    Fish(const std::string& _name, float _speed, float _scale, const std::string& _power, const std::string& _path);
    void computeNonVoidPixelCoordinates(const sf::Sprite& sprite, size_t fishIndex);
    bool checkCollision(const sf::Sprite& target, const sf::Sprite& targetter, size_t fishIndex);
    std::vector<Fish> generateFishes(const std::string& filename);
    void loadTextures(PlayObject& _obj, std::vector<Fish> fishes);
    void moveAI(float deltaTime, PlayObject& _obj, size_t fishIndex, const sf::Sprite& humanFishSprite, std::vector<Fish> fishs, HumanFish& humanFish);
    void animate(float deltaTime, PlayObject& _obj, size_t globalIndex);
    void animateAllFish(float deltaTime, PlayObject& _obj, const sf::Sprite& humanFishSprite, std::vector<Fish>& fishes, HumanFish& humanFish);
    const std::string getName() const;
    const float getSpeed() const;
    const float getScale() const;
    const std::string getPower() const;
    const std::string getPath() const;
    const float getFocus() const;
    void setFocus(float _focus);
};
