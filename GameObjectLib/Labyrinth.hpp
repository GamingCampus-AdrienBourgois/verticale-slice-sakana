#pragma once
#include <vector>
#include "Cell.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"

class Labyrinth : public Sprite_s {
public:
    Labyrinth(const std::string& mapFile);
    ~Labyrinth();

    void LoadMap();
    void Draw(sf::RenderWindow& window);

    void Shoot() {}
    void IncreaseScore(int value) {}
    int GetScore() const {}
    void TakeDamage(float damage) {}

private:
    std::string _mapFilePath;
    std::vector<std::vector<Cell>> _mapGrid;
};
