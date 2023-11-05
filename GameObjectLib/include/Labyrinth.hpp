#pragma once
#include <vector>
#include <string>
#include "Wall.hpp"
#include "Path.hpp"
#include "Window.hpp"
#include "sstream"
#include "fstream"

class Labyrinth {
public:
    Labyrinth(const std::string& mapFilePath) : _mapFilePath(mapFilePath) {}
    void LoadMap(Window_s& window);
    


    bool isCollidingWithWalls(const sf::FloatRect& characterBounds) const;
    bool isCollidingWithPaths(const sf::FloatRect& characterBounds) const;

    std::vector<std::vector<bool>> getMatrice();

private:
    std::vector<std::vector<bool>> _mapGrid;
    std::string _mapFilePath;
    std::vector<Wall> _walls;
    std::vector<Path> _paths;
};
