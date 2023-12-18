#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"

#include <iostream>
class HumanFish {
    PlayObject& _obj;

    // cam
    sf::View &cameraView;
    float zoomFactor;
    float camDelay;

    // animation
    float elapsed;
    int currentFrame;
    bool cloak;
    bool cloaked;

    // move
    std::vector<sf::Vector2f> points;
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
    HumanFish(PlayObject& obj, sf::View &_cameraView) : _obj(obj), cameraView(_cameraView) {
        zoomFactor = 2.f;
        currentFrame = 1;
        elapsed = 0.f;
        camDelay = 0.f;
        speed = 1.f;
        elapsedSize = 0.f;
        isPushing = false;
        pushElapsed = 0.0f;
        pushDelay = 3.0f;
        shaderLoaded = false;
        radius = 400.0f;
        cloak = false;
        cloaked = false;
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
        _obj.globalSprt[GlobalS::HFISH].setPosition(sf::Vector2f((_obj.bgSprt[BackS::MAP].getScale().x * _obj.bgTex[BackS::MAP].getSize().x) / 2, 400));
    }

    void handleEvent(const sf::Event& event, Window_s& window) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LAlt) {
            zoomFactor = 20.f; // Dézoomer de 20 fois
        }
        else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::LAlt) {
                zoomFactor = 2.0f;
            }
            // jump or dash
            else if (event.key.code == sf::Keyboard::Space) {
                if (!isPushing && pushElapsed >= pushDelay) {
                    isPushing = true;
                    pushElapsed = 0.0f; // Réinitialiser le timer de saut
                }

            }
        }
        // cloak
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && cloak) {
            cloaked = true;
            sf::Sprite& fsh = _obj.globalSprt[GlobalS::HFISH];
            fsh.setColor(sf::Color(fsh.getColor().r, fsh.getColor().g, fsh.getColor().b, 100));
        } else if (event.type == sf::Event::KeyReleased) {
            sf::Sprite& fsh = _obj.globalSprt[GlobalS::HFISH];
            fsh.setColor(sf::Color(fsh.getColor().r, fsh.getColor().g, fsh.getColor().b, 255));
            cloaked = false;
        }
    }

    void updateCamera(float deltaTime, Window_s& window) 
    {
        sf::Vector2f humanFishPosition = _obj.globalSprt[GlobalS::HFISH].getPosition();
        sf::Vector2f currentCameraCenter = cameraView.getCenter();
        float lat = 0.1f;
        sf::Vector2f newCameraCenter = currentCameraCenter + lat * (humanFishPosition - currentCameraCenter);

        cameraView.setCenter(newCameraCenter);
        // appliquer le facteur de zoom a la caméra
        cameraView.setSize(window.getWindow().getDefaultView().getSize() * zoomFactor);
        window.getWindow().setView(cameraView);
    }

    bool isNotDead() 
    {
        return (std::abs(_obj.globalSprt[GlobalS::HFISH].getScale().x) > 1.f && std::abs(_obj.globalSprt[GlobalS::HFISH].getScale().y) > 1.f);
    }

    void followMouse(Window_s& window, float deltaTime) 
    {
        if (zoomFactor == 2.0f && !isPushing && isNotDead() && !cloaked) {
            sf::Sprite& fish = _obj.globalSprt[GlobalS::HFISH];
            sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
            sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);
            targetPosition = mousePosF;
            sf::Vector2f currentPosition = fish.getPosition();
            sf::Vector2f direction = targetPosition - currentPosition;
            sf::Vector2f newPosition = currentPosition + speed * deltaTime * direction;

            if (!_obj.checkPixelCollision(fish, _obj.frontSprt[FrontS::MAPBORDER]) && newPosition.y > 0) {
                fish.setPosition(newPosition);
            }
            else {
                // collied;
            }
        }
    }

    void pusher(Window_s& window, float deltaTime, bool isPush) {
        if (isPush) {

            if (isPushing) {
                float pushHeight = 20.f;

                sf::Sprite& fish = _obj.globalSprt[GlobalS::HFISH];
                fish.move(0, -pushHeight + 20.0f * deltaTime);

                pushElapsed += deltaTime;
                if (pushElapsed >= 0.5f) {
                    isPushing = false;
                }
            }
            else {
                pushElapsed += deltaTime;
                if (pushElapsed > pushDelay) {
                    pushElapsed = pushDelay;
                }
            }
        }
        if (!isPush) {
            if (isPushing) {
                float pushHeight = 40.f;

                sf::Sprite& fish = _obj.globalSprt[GlobalS::HFISH];

                if (_obj.globalSprt[GlobalS::HFISH].getScale().x < 0)
                    fish.move(-pushHeight + 50.0f * deltaTime, 0);
                else
                    fish.move(pushHeight + 50.0f * deltaTime, 0);

                pushElapsed += deltaTime;
                if (pushElapsed >= 0.5f) {
                    isPushing = false;
                }
            }
            else {
                pushElapsed += deltaTime;
                if (pushElapsed > pushDelay) {
                    pushElapsed = pushDelay;
                }
            }
        }
    }

    void setSpeed(float _speed) {
        speed = _speed;
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
            sf::Vector2f targetPoint = target.getInverseTransform().transformPoint(worldPoint);
            // std::cout << targetPoint.x << ":" << targetPoint.y << std::endl;

             // Vérifier si le point est dans la zone de texture de la cible
            if ((targetPoint.x > 0 && targetPoint.y > 0) && (targetPoint.x < targetRect.width) && (targetPoint.y < targetRect.height)) {
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
            std::cout << "boom";

        sf::Vector2f spritePos = _obj.globalSprt[GlobalS::HFISH].getPosition();
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window.getWindow());
        sf::Vector2f mouseWorldPos = window.getWindow().mapPixelToCoords(mousePixelPos, cameraView);
        sf::Vector2f direction = mouseWorldPos - spritePos;
        float angle = atan2(direction.y, direction.x) * 180 / M_PI;

        // change x direction
        if (direction.x < 0) {
            angle += 180;
            _obj.globalSprt[GlobalS::HFISH].setScale(-std::abs(_obj.globalSprt[GlobalS::HFISH].getScale().x), _obj.globalSprt[GlobalS::HFISH].getScale().y);
        }
        else {
            _obj.globalSprt[GlobalS::HFISH].setScale(std::abs(_obj.globalSprt[GlobalS::HFISH].getScale().x), _obj.globalSprt[GlobalS::HFISH].getScale().y);
        }
        _obj.globalSprt[GlobalS::HFISH].setRotation(angle);
        // anim
        elapsed += deltaTime;
        if (elapsed >= 0.10f) {
            currentFrame = (currentFrame + 1) % 2;
            elapsed -= 0.10f;
        }
        _obj.globalSprt[GlobalS::HFISH].setTextureRect(sf::IntRect(currentFrame * static_cast<int>(FRAME_WIDTH), 0, static_cast<int>(FRAME_WIDTH), static_cast<int>(FRAME_HEIGHT)));
    }

    void handleObstacleCollision(Window_s& window, MassS type) 
    {
        if (!isNotDead())
            return;

        auto& obstacles = _obj.massSprt[type];
        sf::Sprite& fishSprite = _obj.globalSprt[GlobalS::HFISH];
        sf::FloatRect fishBounds = fishSprite.getGlobalBounds();

        for (auto& obstacle : obstacles) {
            if (fishBounds.intersects(obstacle.getGlobalBounds())) {
                window.removeFromRenderLayer(static_cast<int>(Scene::SPRITESMASS), obstacle);

                sf::Vector2f currentScale = fishSprite.getScale();
                float proportion = static_cast<float>(_obj.globalTex[GlobalS::HFISH].getSize().x / _obj.globalTex[GlobalS::HFISH].getSize().y);
                float reduction = 0.01f;

                std::cout << proportion;

                fishSprite.setScale(currentScale.x - (reduction * proportion), currentScale.y - reduction);

            }
        }
    }

    void handleFishsCollision(Window_s& window) {
        if (!isNotDead())
            return;

        sf::Sprite& humanFishSprite = _obj.globalSprt[GlobalS::HFISH];
        sf::FloatRect humanFishBounds = humanFishSprite.getGlobalBounds();

        for (size_t i = GlobalS::FISHA; i < GlobalS::GEND; i++) {
            sf::Sprite& fishSprite = _obj.globalSprt[i];
            sf::FloatRect fishBounds = fishSprite.getGlobalBounds();
            if (humanFishBounds.intersects(fishBounds)) {
                float scaleReduction = 0.01f;
                sf::Vector2f currentScale = humanFishSprite.getScale();
                if (currentScale.x > 0.5f && currentScale.y > 0.5f) {
                    humanFishSprite.setScale(currentScale.x - scaleReduction, currentScale.y - scaleReduction);
                }
            }
        }
    }


    void checkAndEatAlgae(Window_s& window) {
        auto& algaeSprites = _obj.massSprt[MassS::ALGAES];
        sf::Sprite& fishSprite = _obj.globalSprt[GlobalS::HFISH];
        sf::FloatRect fishBounds = fishSprite.getGlobalBounds();

        for (size_t i = 0; i != algaeSprites.size(); ++i) {
            if (fishBounds.intersects(algaeSprites[i].getGlobalBounds())) {
                window.removeFromRenderLayer(static_cast<int>(Scene::SPRITESMASS), algaeSprites[i]);
                sf::Vector2f currentScale = fishSprite.getScale();
                float proportion = static_cast<float>(_obj.globalTex[GlobalS::HFISH].getSize().x / _obj.globalTex[GlobalS::HFISH].getSize().y);
                fishSprite.setScale(currentScale.x + 0.01f, currentScale.y + (0.01f * proportion));

            }
        }
    }

    void shrinkWithTime(float deltaTime) {
        elapsedSize += deltaTime;

        if (elapsedSize >= 10.f) {
            sf::Vector2f currentScale = _obj.globalSprt[GlobalS::HFISH].getScale();
            float proportion = static_cast<float>(_obj.globalTex[GlobalS::HFISH].getSize().x / _obj.globalTex[GlobalS::HFISH].getSize().y);
            _obj.globalSprt[GlobalS::HFISH].setScale(currentScale.x - (0.03f * proportion), currentScale.y - 0.03f);
            elapsedSize -= 10.f;
        }
    }

    void applyAuraEffect(Window_s& window) {
        if (!shaderLoaded) {
            if (!Rshader.loadFromFile("erase.frag", sf::Shader::Fragment)) {
                throw std::runtime_error("Failed to load shaders");
            }
            shaderLoaded = true;
        }

        sf::Vector2f worldPos = _obj.globalSprt[GlobalS::HFISH].getPosition();
        sf::Vector2i pixelPos = window.getWindow().mapCoordsToPixel(worldPos);
        Rshader.setUniform("mouse", sf::Glsl::Vec2(pixelPos.x, pixelPos.y));
        Rshader.setUniform("radius", radius);

        shaderStates.shader = &Rshader;
        window.replaceFromRenderLayer(static_cast<int>(Scene::FRONT), _obj.frontSprt[FrontS::MAPGRAD], _obj.frontSprt[FrontS::MAPGRAD], shaderStates);
    }

    void setCloack() {
        cloak = true;
    }
};  