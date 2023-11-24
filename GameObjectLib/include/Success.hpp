#pragma once
#include <SFML/Graphics.hpp>

#include "MenuObject.hpp"

class Success : public MenuObject {
	Success() {
		buttonCount = 0;
		_fontButton.loadFromFile("asset/font/Beyonders.ttf");
		_fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
	}
	~Success() = default;



};