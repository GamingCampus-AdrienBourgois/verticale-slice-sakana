#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"

#include <iostream>
class HumanFish {
	PlayObject& _obj;

    sf::View cameraView;
    sf::Vector2f targetPosition;
    float elapsed;
    int currentFrame;

    static constexpr float FRAME_WIDTH = 29.f;
    static constexpr float FRAME_HEIGHT = 21.f;
    static constexpr float M_PI = 3.1416f;


public:
	HumanFish(PlayObject& obj) : _obj(obj) {
        currentFrame = 1;
        elapsed = 0.f;
	}
	void load(Window_s& window) {
        textureSetters(window);
        cameraView.setSize(static_cast<float>(window.getWindow().getSize().x), static_cast<float>(window.getWindow().getSize().y));
        cameraView.setCenter(_obj.globalSprt[GlobalS::HFISH].getPosition().x, _obj.globalSprt[GlobalS::HFISH].getPosition().y);


        std::cout << "test10";
	}


    void textureSetters(Window_s& window) {
        sf::Vector2u windowSize = window.getWindow().getSize();
        float X = static_cast<float>(windowSize.x);
        float Y = static_cast<float>(windowSize.y);

        // load texture and create de sprite 
        std::vector<std::string> globaleFile = {"asset/sprite/fishgame/fishs/HumanFish.png" };

        _obj.globalTex.resize(globaleFile.size());
        _obj.globalSprt.resize(globaleFile.size());

        for (size_t i = 0; i < globaleFile.size(); i++) {
            if (!_obj.globalTex[i].loadFromFile(globaleFile[i])) {
                throw std::runtime_error("Failed to load texture");
            }
            else {
                _obj.globalSprt[i].setTexture(_obj.globalTex[i]);
            }
        }
        _obj.globalSprt[GlobalS::HFISH].setScale(5.f, 5.f);
        _obj.globalSprt[GlobalS::HFISH].setOrigin(FRAME_WIDTH / 2.f, FRAME_HEIGHT / 2.f);

        _obj.globalSprt[GlobalS::HFISH].setPosition(sf::Vector2f(X/2, Y/2));

    }

    void animate(float deltaTime, Window_s &window) 
    {
        sf::Vector2f spritePos = _obj.globalSprt[GlobalS::HFISH].getPosition();
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window.getWindow()));
        sf::Vector2f direction = mousePos - spritePos;

        // trigonometry
        float angle = atan2(direction.y, direction.x) * 180 / M_PI;
        if (direction.x < 0) {
           angle += 180;
            _obj.globalSprt[GlobalS::HFISH].setScale(-std::abs(_obj.globalSprt[GlobalS::HFISH].getScale().x), _obj.globalSprt[GlobalS::HFISH].getScale().y);
        }
        else
            _obj.globalSprt[GlobalS::HFISH].setScale(std::abs(_obj.globalSprt[GlobalS::HFISH].getScale().x), _obj.globalSprt[GlobalS::HFISH].getScale().y);
        // Set the sprite's rotation
        _obj.globalSprt[GlobalS::HFISH].setRotation(angle);

        elapsed += deltaTime;
        if (elapsed >= 0.10f) {
            currentFrame = (currentFrame + 1) % 2;
            elapsed -= 0.10f;
        }
        _obj.globalSprt[GlobalS::HFISH].setTextureRect(sf::IntRect(currentFrame * static_cast<int>(FRAME_WIDTH), 0, static_cast<int>(FRAME_WIDTH), static_cast<int>(FRAME_HEIGHT)));

    }

    void handleEvent(const sf::Event& event, Window_s& window, Music& music) {
        // Check for arrow key presses and update targetPosition accordingly
        if (event.type == sf::Event::KeyPressed) {
            const float moveDistance = 10.f; // Distance to move on each key press
            switch (event.key.code) {
            case sf::Keyboard::Left:
                targetPosition.x -= moveDistance;
                break;
            case sf::Keyboard::Right:
                targetPosition.x += moveDistance;
                break;
            case sf::Keyboard::Up:
                targetPosition.y -= moveDistance;
                break;
            case sf::Keyboard::Down:
                targetPosition.y += moveDistance;
                break;
            default:
                break;
            }
        }
    }

    void followMouse(Window_s& window, float deltaTime) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
        sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);


        targetPosition = mousePosF;

        sf::Vector2f currentPosition = _obj.globalSprt[GlobalS::HFISH].getPosition();

        float lerpFactor = deltaTime; // Adjust this factor for smoothness
        sf::Vector2f newPosition = currentPosition + lerpFactor * (targetPosition - currentPosition);

        _obj.globalSprt[GlobalS::HFISH].setPosition(newPosition);

        cameraView.setCenter(newPosition);

        window.getWindow().setView(cameraView);
    }


};
