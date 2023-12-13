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
public:


    Fish(const std::string& _name, float _speed, float _scale, const std::string& _power, const std::string &_path)
        : name(_name), speed(_speed), scale(_scale), power(_power), path(_path) {}
    Fish() {};


    static std::vector<Fish> generateFishes(const std::string& filename) {
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
