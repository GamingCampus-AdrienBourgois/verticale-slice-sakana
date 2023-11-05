#include "Labyrinth.hpp"

void Labyrinth::LoadMap(Window_s &window) {
    std::ifstream file(_mapFilePath);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<bool> row;
        std::istringstream iss(line);
        char ch;
        while (iss >> ch) {
            if (ch == '0') 
                row.push_back(false);
            else  {
                if (ch == '1') 
                    row.push_back(true);
            }
        }
        _mapGrid.push_back(row);
    }

    size_t maxRow = 0;
    for (const auto& row : _mapGrid) {
        if (row.size() > maxRow) {
            maxRow = row.size();
        }
    }
    _walls.reserve(_mapGrid.size() * maxRow);
    _paths.reserve(_mapGrid.size() * maxRow);

    for (size_t i = 0; i < _mapGrid.size(); i++) {
        for (size_t j = 0; j < _mapGrid[i].size(); j++) {
            if (_mapGrid[i][j]) {
                _walls.emplace_back(j * Wall::WIDTH, i * Wall::HEIGHT);
                _walls.back().draw(window);
            } else {
                _paths.emplace_back(j * Path::WIDTH, i * Path::HEIGHT);
                _paths.back().draw(window);
            }
        }
    }

}
//#include <iostream>
bool Labyrinth::isCollidingWithWalls(const sf::FloatRect& characterBounds) const {
    for (const auto& wall : _walls) {
        if (wall.getBounds().intersects(characterBounds)) {
            //std::cout << "trigered\n";
            return true;
        }
    }
    return false;
}
bool Labyrinth::isCollidingWithPaths(const sf::FloatRect& characterBounds) const {
    for (const auto& path : _paths) {
        if (path.getBounds().intersects(characterBounds)) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<bool>> Labyrinth::getMatrice() {
    return _mapGrid;
}