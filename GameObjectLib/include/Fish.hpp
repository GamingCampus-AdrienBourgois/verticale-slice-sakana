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

    int currentFrame;
    float elapsed;
public:

    Fish() = default;

    Fish(const std::string& _name, float _speed, float _scale, const std::string& _power, const std::string& _path)
        : name(_name), speed(_speed), scale(_scale), power(_power), path(_path), elapsed(0), currentFrame(0)
    {
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
                fishes.emplace_back(name, speed, scale, power, path); // Créer un poisson et l'ajouter à la liste
            }

        }

        return fishes;
    }



    void loadTextures(PlayObject& _obj, size_t i, std::vector<Fish> fishes) {
        size_t idx = i - GlobalS::FISHA;

            if (!_obj.globalTex[i].loadFromFile(fishes[idx].getPath())) {
                throw std::runtime_error("Failed to load fish texture: " + fishes[idx].getPath());
            }
            _obj.globalSprt[i].setTexture(_obj.globalTex[i]);
            _obj.globalSprt[i].setScale(fishes[idx].getScale(), fishes[idx].getScale());

            _obj.globalSprt[i].setOrigin(_obj.globalTex[i].getSize().x / 2.f, _obj.globalTex[i].getSize().x / 2.f);

            _obj.globalSprt[i].setPosition(sf::Vector2f(1000, 500));
            std::cout << "prok";
    }

    void moveAI(float deltaTime, PlayObject& _obj, size_t fishIndex, const sf::Sprite& humanFishSprite) {
        // Position du poisson humain
        sf::Vector2f humanFishPos = humanFishSprite.getPosition();

        // Position actuelle de ce poisson
        sf::Vector2f fishPos = _obj.globalSprt[fishIndex].getPosition();

        // Calcul de la distance au poisson humain
        float distance = std::sqrt(std::pow(humanFishPos.x - fishPos.x, 2) + std::pow(humanFishPos.y - fishPos.y, 2));

        // Si la distance est inférieure à un certain seuil, suivez le poisson humain
        const float followDistance = 200.0f; // Distance pour commencer à suivre le poisson humain
        sf::Vector2f movement;

        if (distance < followDistance) {
            // Suivre le poisson humain
            sf::Vector2f direction = humanFishPos - fishPos;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length; // Normaliser le vecteur de direction

            movement = direction * speed * deltaTime;
        }
        else {
            // Mouvement aléatoire
            movement = sf::Vector2f(static_cast<float>(rand() % 3 - 1), static_cast<float>(rand() % 3 - 1)) * speed * deltaTime;
        }

        // Appliquer le mouvement
        _obj.globalSprt[fishIndex].move(movement);

        // Orientez le sprite en fonction de la direction du mouvement
        if (movement.x < 0) {
            _obj.globalSprt[fishIndex].setScale(-std::abs(_obj.globalSprt[fishIndex].getScale().x), _obj.globalSprt[fishIndex].getScale().y);
        }
        else {
            _obj.globalSprt[fishIndex].setScale(std::abs(_obj.globalSprt[fishIndex].getScale().x), _obj.globalSprt[fishIndex].getScale().y);
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
