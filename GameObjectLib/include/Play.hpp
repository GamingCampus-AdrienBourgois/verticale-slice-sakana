#pragma once
#include <SFML/Graphics.hpp>

#include "MenuObject.hpp"

class Play : public MenuObject {


public:
	Play();
	~Play() = default;

	void load(Window_s& window);

};