﻿#include "Fish.hpp"

Fish::Fish() : currentFrame(0), elapsed(0), speed(0), scale(0), focus(1500)
{
    colidedVec.resize(static_cast<size_t>(GlobalS::GEND - GlobalS::FISHA) + 1);
    for (auto colided : colidedVec) {
        colided = false;
    }
    depthVec.resize(static_cast<size_t>(GlobalS::GEND - GlobalS::FISHA) + 1);

    timeSinceLastDirectionChange.resize(static_cast<size_t>(GlobalS::GEND - GlobalS::FISHA) + 1, 0.0f);

}

Fish::Fish(const std::string& _name, float _speed, float _scale, const std::string& _power, const std::string& _path)
    : name(_name), speed(_speed), scale(_scale), power(_power), path(_path), elapsed(0), currentFrame(0), focus(1500)
{
    colidedVec.resize(static_cast<size_t>(GlobalS::GEND - GlobalS::FISHA) + 1);
    for (auto colided : colidedVec) {
        colided = false;
    }
    depthVec.resize(static_cast<size_t>(GlobalS::GEND - GlobalS::FISHA) + 1);

    timeSinceLastDirectionChange.resize(static_cast<size_t>(GlobalS::GEND - GlobalS::FISHA) + 1, 0.0f);

}

void Fish::computeNonVoidPixelCoordinates(const sf::Sprite& sprite, size_t fishIndex) {
    std::vector<sf::Vector2i> coordinates;
    const sf::Texture* texture = sprite.getTexture();
    const sf::IntRect& rect = sprite.getTextureRect();
    const sf::Image& image = texture->copyToImage();

    for (int x = rect.left; x < rect.left + rect.width; ++x) {
        for (int y = rect.top; y < rect.top + rect.height; ++y) {
            if (image.getPixel(x, y).a != 0) {
                coordinates.push_back(sf::Vector2i(x, y));
            }
        }
    }
    nonVoidPixelCoordinatesMap[fishIndex] = coordinates;
}

bool Fish::checkCollision(const sf::Sprite& target, const sf::Sprite& targetter, size_t fishIndex) {

    const auto& targetterCoordinates = nonVoidPixelCoordinatesMap[fishIndex];

    const sf::Texture* targetTexture = target.getTexture();
    const sf::Image& targetImage = targetTexture->copyToImage();
    sf::Transform targetInverseTransform = target.getInverseTransform();
    sf::Transform targetterTransform = targetter.getTransform();

    for (const auto& coord : targetterCoordinates) {
        sf::Vector2f transformedCoord = targetterTransform.transformPoint(static_cast<float>(coord.x), static_cast<float>(coord.y));
        sf::Vector2i targetImageCoord = static_cast<sf::Vector2i>(targetInverseTransform.transformPoint(transformedCoord));

        if (targetImageCoord.x >= 0 && targetImageCoord.x < static_cast<int>(targetTexture->getSize().x) &&
            targetImageCoord.y >= 0 && targetImageCoord.y < static_cast<int>(targetTexture->getSize().y)) {
            if (targetImage.getPixel(targetImageCoord.x, targetImageCoord.y).a != 0) {
                return true;
            }
        }
    }
    return false;
}


std::vector<Fish> Fish::generateFishes(const std::string& filename) {
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



void Fish::loadTextures(PlayObject& _obj, std::vector<Fish> fishes) {
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

        // load collision points
        computeNonVoidPixelCoordinates(_obj.globalSprt[i], i);
    }




}




void Fish::moveAI(float deltaTime, PlayObject& _obj, size_t fishIndex, const sf::Sprite& humanFishSprite, std::vector<Fish> fishs, HumanFish& humanFish) {
    sf::Sprite& fishSprite = _obj.globalSprt[fishIndex];
    if (_obj.globalSprt[GlobalS::HOOK].getGlobalBounds().intersects(fishSprite.getGlobalBounds()))
        return;
    int fishsIdx = static_cast<int>(fishIndex) - static_cast<int>(GlobalS::FISHA);
    float ms = fishs[fishsIdx].getSpeed();
    sf::Vector2f fishPos = fishSprite.getPosition();
    sf::Vector2f humanFishPos = humanFishSprite.getPosition();
    float depthLimit = 500.0f;
    float depthBase = depthVec[fishsIdx];
    float directionX = 0.f;

    timeSinceLastDirectionChange[fishsIdx] += deltaTime;

    // changer la position
    if (timeSinceLastDirectionChange[fishsIdx] >= 5.0f) {
        if (rand() % 3 == 0) { // 1 chance sur 3 de changer de direction
            colidedVec[fishsIdx] = !colidedVec[fishsIdx];
        }
        timeSinceLastDirectionChange[fishsIdx] = 0.0f; // Réinitialiser le compteur
    }
    if (fishSprite.getPosition().x < 5400.f || fishSprite.getPosition().x > 28000.f) {
        colidedVec[fishsIdx] = !colidedVec[fishsIdx];
    }

    if (colidedVec[fishsIdx]) {
        directionX = (fishIndex % 2 == 0) ? -1.0f : 1.0f; // Alternance des directions
    }
    else {
        directionX = (fishIndex % 2 == 0) ? 1.0f : -1.0f;
    }

    // distance pour suivre le poisson humain
    float distanceToHumanFish = std::hypot(humanFishPos.x - fishPos.x, humanFishPos.y - fishPos.y);
    // movement total du poisson
    sf::Vector2f movement;

    if (distanceToHumanFish < focus && humanFishPos != fishPos && !humanFish.getCloak()) {
        // suivre le poisson humain
        humanFishPos.y -= 50.f;
        sf::Vector2f direction = humanFishPos - fishPos;
        float length = std::hypot(direction.x, direction.y);

        direction /= length; // Normaliser
        // deplacement
        movement.x = direction.x * ms * deltaTime;
        movement.y = direction.y * ms * deltaTime;
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








void Fish::animate(float deltaTime, PlayObject& _obj, size_t globalIndex) {
    elapsed += deltaTime;
    if (elapsed >= 0.1f) {

        float width = static_cast<float>(_obj.globalTex[globalIndex].getSize().x) / 2.1f;
        float height = static_cast<float>(_obj.globalTex[globalIndex].getSize().y);

        currentFrame = (currentFrame + 1) % 2;
        _obj.globalSprt[globalIndex].setTextureRect(sf::IntRect(currentFrame * static_cast<int>(width), 0, static_cast<int>(width), static_cast<int>(height)));

        elapsed -= 0.1f;


    }
}
void Fish::animateAllFish(float deltaTime, PlayObject& _obj, const sf::Sprite& humanFishSprite, std::vector<Fish>& fishes, HumanFish& humanFish) {
    for (size_t i = GlobalS::FISHA; i < GlobalS::GEND; i++) {
        int fishIdx = static_cast<int>(i) - static_cast<int>(GlobalS::FISHA);
        moveAI(deltaTime, _obj, i, humanFishSprite, fishes, humanFish);
        fishes[fishIdx].animate(deltaTime, _obj, i);
    }
}



const std::string Fish::getName() const {
    return name;
}
const float Fish::getSpeed() const {
    return speed;
}
const float Fish::getScale() const {
    return scale;
}
const std::string Fish::getPower() const {
    return power;
}
const std::string Fish::getPath() const {
    return path;
}
const float Fish::getFocus() const {
    return focus;
}
void Fish::setFocus(float _focus) {
    focus = _focus;
}