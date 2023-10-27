#pragma once
#include "Window.hpp"

class GameObject {
public:
    GameObject() {}
    virtual ~GameObject() = default;

    virtual void setPosition(float x, float y) {}
    virtual void setDirection(int dir) {}
    virtual void update(float deltaTime) {}
    virtual void draw(Window_s& window) {}
    virtual void setSize(float x, float y) {}

};