#pragma once

#include "MenuObject.hpp"
#include "Music.hpp"
#include "Window.hpp"

class Credit : public MenuObject
{
	float elapsed;

public:
	Credit();
	~Credit() override = default;

	void load(Window_s& window) override;
	void scroller(float deltaTime, Music& music);
	void textureSetters(Window_s& window);
};
