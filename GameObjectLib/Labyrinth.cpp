#include "Labyrinth.hpp"
#include <fstream>
#include <sstream>

Labyrinth::Labyrinth(const std::string& mapFile) : _mapFilePath(mapFile) {
    LoadMap();
}

Labyrinth::~Labyrinth() {}

void Labyrinth::LoadMap() {
    // load dans _MapGrid
}

void Labyrinth::Draw(sf::RenderWindow& window) {
    // temp draw
}
