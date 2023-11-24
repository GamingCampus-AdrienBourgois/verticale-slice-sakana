#pragma once
#include <SFML/Graphics.hpp>

#include "MenuObject.hpp"

class Help : public MenuObject {
	
public:
	Help();
	~Help() = default;

	void load(Window_s& window);
};