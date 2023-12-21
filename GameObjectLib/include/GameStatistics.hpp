#pragma once
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class GameStatistics {
public:
    GameStatistics();
    void incrementGameStarts();
    void incrementClicks();
    void updateGameTime(float deltaTime);
    void saveStatistics();
    void loadStatistics();
    std::string getTotalGameTime() const;

    static std::string getParamFromString(std::string param, const std::string& file); // utilisable partout dans le code car la fonction est utile
    static void saveSettingsValue(const std::string& param, const std::string& file, const std::string& newValue); // utilisable partout dans le code car la fonction est utile

    unsigned int getGameStarts() const;
    unsigned int getClicks() const;

private:
    unsigned int gameStarts = 0;
    unsigned int clicks = 0;
    float totalTime = 0.0f;
    float bestTime = 0.f;
    std::string _file;
};
