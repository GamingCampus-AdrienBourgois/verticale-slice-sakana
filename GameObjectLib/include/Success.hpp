#pragma once
#include <SFML/Graphics.hpp>

#include "MenuObject.hpp"
#include "Window.hpp"
#include "GameStatistics.hpp"

// This class purpose is only to load the saveStatistics class and make success out of it the GameStatistique does everything
class Success : public MenuObject {
	std::string file;
	float elapsed;

	bool timeS;
	bool clickS;
	bool openS;

public:
	Success();
	~Success() = default;

	void textureSetters(Window_s& window);
	void load(Window_s& window);
	void update(float deltaTime);
};    