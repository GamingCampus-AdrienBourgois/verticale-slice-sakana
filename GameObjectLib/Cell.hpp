#pragma once
#include "Sprite.hpp"

class Cell : public Sprite_s {
public:
    enum CellType { WALL, PATH };
    Cell(float x, float y, CellType type);
};

