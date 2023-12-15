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
    std::vector<sf::Vector2f> points;
    float zoomFactor;

    static constexpr float FRAME_WIDTH = 29.f;
    static constexpr float FRAME_HEIGHT = 21.f;
    static constexpr float M_PI = 3.1416f;
public:
	HumanFish(PlayObject& obj) : _obj(obj) {
        zoomFactor = 2.f;
        currentFrame = 1;
        elapsed = 0.f;
	}

	void load(Window_s& window) {
        textureSetters(window);
        cameraView.setSize(static_cast<float>(window.getWindow().getSize().x), static_cast<float>(window.getWindow().getSize().y));
        cameraView.setCenter(_obj.globalSprt[GlobalS::HFISH].getPosition().x, _obj.globalSprt[GlobalS::HFISH].getPosition().y);

        points = loadCollisionPoints(_obj.globalSprt[GlobalS::HFISH]);
	}

    void textureSetters(Window_s& window) {
        // load texture and create de sprite 
        if (!_obj.globalTex[GlobalS::HFISH].loadFromFile("asset/sprite/fishgame/fishs/HumanFish.png")) {
            throw std::runtime_error("Failed to load HumanFish texture");
        }
        _obj.globalSprt[GlobalS::HFISH].setTexture(_obj.globalTex[GlobalS::HFISH]);
        _obj.globalSprt[GlobalS::HFISH].setScale(5.f, 5.f);
        _obj.globalSprt[GlobalS::HFISH].setOrigin(FRAME_WIDTH / 2.f, FRAME_HEIGHT / 2.f);
        _obj.globalSprt[GlobalS::HFISH].setPosition(sf::Vector2f((_obj.bgSprt[BackS::MAP].getScale().x * _obj.bgTex[BackS::MAP].getSize().x)/2, 400));
    }

    void handleEvent(const sf::Event& event, Window_s& window) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            // Zoom out quand la touche espace est press
            zoomFactor = 20.f; // Dézoomer de 20 fois

            
        }
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
            // Zoom in (retour à la normale) quand la touche espace est release
            zoomFactor = 2.0f;
        }
    }

    void updateCamera(float deltaTime, Window_s& window) {
        // maj de la position de la camera pour suivre le poisson humain
        sf::Vector2f humanFishPosition = _obj.globalSprt[GlobalS::HFISH].getPosition();
        cameraView.setCenter(humanFishPosition);

        // appliquer le facteur de zoom a la caméra
        cameraView.setSize(window.getWindow().getDefaultView().getSize() * zoomFactor);
        window.getWindow().setView(cameraView);
    }


    void followMouse(Window_s& window, float deltaTime) {
        if (zoomFactor == 2.0f) {
            sf::Sprite& fish = _obj.globalSprt[GlobalS::HFISH];
            sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
            sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);
            targetPosition = mousePosF;
            sf::Vector2f currentPosition = fish.getPosition();

            // Calculez la nouvelle position potentielle
            sf::Vector2f direction = targetPosition - currentPosition;
            sf::Vector2f newPosition = currentPosition + deltaTime * direction;



            // Vérifiez si une collision se produit avec la nouvelle position
            if (!_obj.checkPixelCollision(fish, _obj.frontSprt[FrontS::MAPBORDER]) && newPosition.y > 0) {
                // Mettez à jour la position seulement s'il n'y a pas de collision
              
               
            }
            fish.setPosition(newPosition);

        }
    }



















    std::vector<sf::Vector2f> loadCollisionPoints(const sf::Sprite& sprite) {
        std::vector<sf::Vector2f> collisionPoints;
        sf::Image image = sprite.getTexture()->copyToImage();
        sf::IntRect rect = sprite.getTextureRect();

        // Parcourir le bord supérieur
        for (int x = 0; x < rect.width; ++x) {
            for (int y = 0; y < rect.height; ++y) {
                sf::Color color = image.getPixel(x + rect.left, y + rect.top);
                if (color.a != 0) {
                    collisionPoints.push_back(sprite.getTransform().transformPoint(static_cast<float>(x), static_cast<float>(y)));
                    break; // Passer au prochain x après avoir trouvé un pixel non transparent
                }
            }
        }

        // Parcourir le bord inférieur
        for (int x = 0; x < rect.width; ++x) {
            for (int y = rect.height - 1; y >= 0; --y) {
                sf::Color color = image.getPixel(x + rect.left, y + rect.top);
                if (color.a != 0) {
                    collisionPoints.push_back(sprite.getTransform().transformPoint(static_cast<float>(x), static_cast<float>(y)));
                    break; // Passer au prochain x après avoir trouvé un pixel non transparent
                }
            }
        }

        // Parcourir le bord gauche
        for (int y = 0; y < rect.height; ++y) {
            for (int x = 0; x < rect.width; ++x) {
                sf::Color color = image.getPixel(x + rect.left, y + rect.top);
                if (color.a != 0) {
                    collisionPoints.push_back(sprite.getTransform().transformPoint(static_cast<float>(x), static_cast<float>(y)));
                    break; // Passer au prochain y après avoir trouvé un pixel non transparent
                }
            }
        }

        // Parcourir le bord droit
        for (int y = 0; y < rect.height; ++y) {
            for (int x = rect.width - 1; x >= 0; --x) {
                sf::Color color = image.getPixel(x + rect.left, y + rect.top);
                if (color.a != 0) {
                    collisionPoints.push_back(sprite.getTransform().transformPoint(static_cast<float>(x), static_cast<float>(y)));
                    break; // Passer au prochain y après avoir trouvé un pixel non transparent
                }
            }
        }

        return collisionPoints;
    }

    void checkAndEatAlgae() {
        auto& algaeSprites = _obj.massSprt[MassS::ALGAES];
        sf::Sprite& fishSprite = _obj.globalSprt[GlobalS::HFISH];

        for (auto it = algaeSprites.begin(); it != algaeSprites.end(); ) {
            if (checkPixelCollision(fishSprite, *it)) {
                // Eat the algae and grow the fish
                it = algaeSprites.erase(it);
                sf::Vector2f currentScale = fishSprite.getScale();
                fishSprite.setScale(currentScale.x + 0.05f, currentScale.y + 0.05f);
            }
            else {
                ++it;
            }
        }
    }



    bool checkPixelCollision(const sf::Sprite& tracker, const sf::Sprite& target, const std::vector<sf::Vector2f>& points) {
        // Assurez-vous que les rectangles englobants se croisent
        if (!tracker.getGlobalBounds().intersects(target.getGlobalBounds())) {
            return false;
        }

        // Convertir les textures des sprites en images pour l'accès aux pixels
        sf::Image targetImage = target.getTexture()->copyToImage();
        sf::IntRect targetRect = target.getTextureRect();

        for (const auto& point : points) {
            // Transformer le point dans le système de coordonnées du tracker au monde
            sf::Vector2f worldPoint = tracker.getTransform().transformPoint(point);

            // Prendre en compte l'échelle du sprite cible
            sf::Vector2f scaledTargetPoint = sf::Vector2f(worldPoint.x / target.getScale().x, worldPoint.y / target.getScale().y);

            // Transformer le point du monde au système de coordonnées de la cible
            sf::Vector2f targetPoint = target.getInverseTransform().transformPoint(scaledTargetPoint);

            // Vérifier si le point est dans la zone de texture de la cible
            if (targetPoint.x > 0 && targetPoint.y > 0 && targetPoint.x < targetRect.width && targetPoint.y < targetRect.height) {
                sf::Color color = targetImage.getPixel(static_cast<unsigned int>(targetPoint.x + targetRect.left), static_cast<unsigned int>(targetPoint.y + targetRect.top));

                // Vérifier si le pixel n'est pas transparent
                if (color.a != 0) {
                    return true;  // Collision détectée
                }
            }
        }

        return false; // Aucune collision
    }



void animate(float deltaTime, Window_s& window) {
    if (checkPixelCollision(_obj.globalSprt[GlobalS::HFISH], _obj.frontSprt[FrontS::MAPBORDER], points))
        std::cout << "test";


    sf::Vector2f spritePos = _obj.globalSprt[GlobalS::HFISH].getPosition();

    // Convert the mouse position to world coordinates relative to the camera view
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window.getWindow());
    sf::Vector2f mouseWorldPos = window.getWindow().mapPixelToCoords(mousePixelPos, cameraView);

    sf::Vector2f direction = mouseWorldPos - spritePos;

    float angle = atan2(direction.y, direction.x) * 180 / M_PI;

    if (direction.x < 0) {
        angle += 180;
        _obj.globalSprt[GlobalS::HFISH].setScale(-std::abs(_obj.globalSprt[GlobalS::HFISH].getScale().x), _obj.globalSprt[GlobalS::HFISH].getScale().y);
    }
    else {
        _obj.globalSprt[GlobalS::HFISH].setScale(std::abs(_obj.globalSprt[GlobalS::HFISH].getScale().x), _obj.globalSprt[GlobalS::HFISH].getScale().y);
    }
    _obj.globalSprt[GlobalS::HFISH].setRotation(angle);


    elapsed += deltaTime;
    if (elapsed >= 0.10f) {
        currentFrame = (currentFrame + 1) % 2;
        elapsed -= 0.10f;
    }
    _obj.globalSprt[GlobalS::HFISH].setTextureRect(sf::IntRect(currentFrame * static_cast<int>(FRAME_WIDTH), 0, static_cast<int>(FRAME_WIDTH), static_cast<int>(FRAME_HEIGHT)));


    checkAndEatAlgae();

}



};