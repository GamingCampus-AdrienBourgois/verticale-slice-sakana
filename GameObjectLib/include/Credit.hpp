#pragma once
#include <SFML/Graphics.hpp>

#include "MenuObject.hpp"
#include "Window.hpp"
#include "Music.hpp"

class Credit : public MenuObject 
{
	float elapsed;

public:
	Credit();
	~Credit() = default;

	void load(Window_s& window);
	void scroller(float deltaTime, Music &music);
	void textureSetters(Window_s& window);
};