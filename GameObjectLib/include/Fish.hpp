#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include <string>
#include <vector>
#include <iostream>

class Fish {
    std::string name;
    float speed;
    float scale;
    std::string power;
    std::string path;

    std::vector<bool> colidedVec;
    std::vector<float> depthVec;

    int currentFrame;
    float elapsed;


public:

    Fish() : currentFrame(0), elapsed(0), speed(0), scale(0)
    {
        colidedVec.resize(static_cast<size_t>(GlobalS::GEND - GlobalS::FISHA) + 1);
        for (auto colided : colidedVec) {
            colided = false;
        }
        depthVec.resize(static_cast<size_t>(GlobalS::GEND - GlobalS::FISHA) + 1);
    }

    Fish(const std::string& _name, float _speed, float _scale, const std::string& _power, const std::string& _path)
        : name(_name), speed(_speed), scale(_scale), power(_power), path(_path), elapsed(0), currentFrame(0)
    {
        colidedVec.resize(static_cast<size_t>(GlobalS::GEND - GlobalS::FISHA) + 1);
        for (auto colided : colidedVec) {
            colided = false;
        }
        depthVec.resize(static_cast<size_t>(GlobalS::GEND - GlobalS::FISHA) + 1);
    }


    std::vector<Fish> generateFishes(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        std::vector<Fish> fishes;

        std::string name, power, path;
        float speed, scale;

        while (std::getline(file, line)) {
            if (line.find("Name=") != std::string::npos) {
                name = line.substr(5);
            }
            else if (line.find("Speed=") != std::string::npos) {
                speed = std::stof(line.substr(6));
            }
            else if (line.find("Scale=") != std::string::npos) {
                scale = std::stof(line.substr(6));
            }
            else if (line.find("Power=") != std::string::npos) {
                power = line.substr(6);
            }
            else if (line.find("Path=") != std::string::npos) {
                path = line.substr(5);
                fishes.emplace_back(name, speed, scale, power, path); // Cr�er un poisson et l'ajouter � la liste
            }

        }

        return fishes;
    }



    void loadTextures(PlayObject& _obj, std::vector<Fish> fishes) {
        for (size_t i = GlobalS::FISHA; i < GlobalS::GEND; i++) {
            size_t idx = i - GlobalS::FISHA;

            if (!_obj.globalTex[i].loadFromFile(fishes[idx].getPath())) {
                throw std::runtime_error("Failed to load fish texture: " + fishes[idx].getPath());
            }
            _obj.globalSprt[i].setTexture(_obj.globalTex[i]);
            _obj.globalSprt[i].setScale(fishes[idx].getScale(), fishes[idx].getScale());
            _obj.globalSprt[i].setOrigin((_obj.globalTex[i].getSize().x / 2.f) / 2.f, _obj.globalTex[i].getSize().y / 2.f);

            float X = (_obj.bgSprt[BackS::MAP].getScale().x * _obj.bgTex[BackS::MAP].getSize().x) / 2.f; // pos at x (middle of map)
            float Y = (_obj.bgSprt[BackS::MAP].getScale().y * _obj.bgTex[BackS::MAP].getSize().y) / (GlobalS::GEND - GlobalS::FISHA + 1); // pos the more the fish is a big idx the deepest he is

            depthVec[idx] = Y * (idx + 1);
            _obj.globalSprt[i].setPosition(sf::Vector2f(X, depthVec[idx]));
        }

    }




    void moveAI(float deltaTime, PlayObject& _obj, size_t fishIndex, const sf::Sprite& humanFishSprite, std::vector<Fish> fishs) {
        int fishsIdx = fishIndex - GlobalS::FISHA;
        float ms = fishs[fishsIdx].getSpeed();
        sf::Sprite& fishSprite = _obj.globalSprt[fishIndex];
        sf::Vector2f fishPos = fishSprite.getPosition();
        sf::Vector2f humanFishPos = humanFishSprite.getPosition();
        // limite de profondeur
        float depthLimit = 500.0f;
        float depthBase = depthVec[fishsIdx]; // Chaque poisson a sa propre profondeur de base
        // determiner la direction du mouvement en X

         // gerer les collisions avec les bords de la carte
        
        float directionX = 0.f;
        /*
        if (_obj.checkPixelCollision(fishSprite, _obj.frontSprt[FrontS::MAPBORDER])) {
            colidedVec[fishsIdx] = (colidedVec[fishsIdx] ? false : true);
        }
        */
        if (colidedVec[fishsIdx]) {
            directionX = (fishIndex % 2 == 0) ? -1.0f : 1.0f; // Alternance des directions
        }
        else {
            directionX = (fishIndex % 2 == 0) ? 1.0f : -1.0f; // Alternance des directions
        }

        // distance pour suivre le poisson humain
        const float followDistance = 2000.0f;
        float distanceToHumanFish = std::hypot(humanFishPos.x - fishPos.x, humanFishPos.y - fishPos.y);
        // movement total du poisson
        sf::Vector2f movement;

        if (distanceToHumanFish < followDistance && humanFishPos != fishPos) {
            // suivre le poisson humain
            sf::Vector2f direction = humanFishPos - fishPos;
            float length = std::hypot(direction.x, direction.y);
            direction /= length; // Normaliser
            // deplacement
            movement = direction * ms * deltaTime;
        }
        else {
            // mouvement normal
            movement.x = directionX * ms * deltaTime;
            // empecher le mouvement en Y � une certaine profondeur
            float newY = fishPos.y + ((rand() % 3 - 1) * ms * deltaTime);
            newY = std::max(depthBase - depthLimit, std::min(newY, depthBase + depthLimit));
            movement.y = newY - fishPos.y;
        }
        // orientation en fonction du mouvement
        if (movement.x < 0) {
            fishSprite.setScale(-std::abs(fishSprite.getScale().x), fishSprite.getScale().y);
        }
        else if (movement.x > 0) {
            fishSprite.setScale(std::abs(fishSprite.getScale().x), fishSprite.getScale().y);
        }

        // appliquer le mouvement
        fishSprite.move(movement);

        // V�rifier si le poisson sort de la profondeur autoris�e
        if (fishPos.y < depthBase - depthLimit || fishPos.y > depthBase + depthLimit) {
            fishSprite.setPosition(fishPos.x, std::min(std::max(fishPos.y, depthBase - depthLimit), depthBase + depthLimit));
        }
    }








    void animate(float deltaTime, PlayObject& _obj, size_t globalIndex) {
        elapsed += deltaTime;
        if (elapsed >= 0.1f) {

            float width = static_cast<float>(_obj.globalTex[globalIndex].getSize().x) / 2.1f;
            float height = static_cast<float>(_obj.globalTex[globalIndex].getSize().y);

            currentFrame = (currentFrame + 1) % 2;
            _obj.globalSprt[globalIndex].setTextureRect(sf::IntRect(currentFrame * static_cast<int>(width), 0, static_cast<int>(width), static_cast<int>(height)));

            elapsed -= 0.1f;


        }
    }
    void animateAllFish(float deltaTime, PlayObject& _obj, const sf::Sprite& humanFishSprite, std::vector<Fish>& fishes) {
        for (size_t i = GlobalS::FISHA; i < GlobalS::GEND; i++) {
            int fishIdx = i - GlobalS::FISHA;
            moveAI(deltaTime, _obj, i, humanFishSprite, fishes);
            fishes[fishIdx].animate(deltaTime, _obj, i);
        }
    }

    const std::string getName() const {
        return name;
    }
    const float getSpeed() const {
        return speed;
    }
    const float getScale() const {
        return scale;
    }
    const std::string getPower() const {
        return power;
    }
    const std::string getPath() const {
        return path;
    }

};
