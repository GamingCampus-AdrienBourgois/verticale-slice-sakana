#include "Cell.hpp"

Cell::Cell(float x, float y, CellType type)
    : Sprite_s(type == WALL ? "path1.png" : "path2.png") {
    SetPosition(x, y);
}
