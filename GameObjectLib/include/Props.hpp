#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include <random>

#define _CAN_ 50
#define _WOOD_ 50
#define _TRASH1_ 50
#define _TRASH2_ 50
#define _ALGAE_ 100

class Props {
    PlayObject& _obj;
    float elapsed;
    int frame;

    bool fishingRodActive;
    bool fishingRodDescending;
    float fishingRodSpeed;
    float fishingRodMaxY;
    float fishingRodMinY;

    float fishingRodElapsedStart;

    std::mt19937 gen;
    std::random_device rd;

    std::map<size_t, float> obstacleDelays;
    size_t nextObstacleId;

    int can;
    int wood;
    int trash1;
    int trash2;
    int algae;

    bool caught;

public:
    Props(PlayObject& obj);
    void textureSetters(Window_s& window);
    void animateFishingRod(float deltaTime, Window_s& window);
    void setCaught(bool _caught);
    bool getCaught();
    void animateSpecificObstacle(float deltaTime, std::vector<sf::Sprite>& obstacles, Window_s& window);
    float calculateRotationSpeed(float yPos, float maxY);
    float calculateMoveSpeed(float yPos, float maxY);
    void generateAlgae(Window_s& window, int count);
    void generateObstacles(Window_s& window, int count, GlobalS textureId, MassS spriteId);
    void load(Window_s& window);
    void animate(float deltaTime, Window_s& window);
    void animateAlgae(float deltaTime, Window_s& window);
    void handleEvent(const sf::Event& event, Window_s& window, Music& music);

    int getCan() const;
    void setCan(int value);
    int getWood() const;
    void setWood(int value);
    int getTrash1() const;
    void setTrash1(int value);
    int getTrash2() const;
    void setTrash2(int value);
    int getAlgae() const;
    void setAlgae(int value);
};
