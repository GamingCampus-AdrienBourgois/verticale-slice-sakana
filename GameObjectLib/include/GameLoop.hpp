#pragma once
#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "GameStatistics.hpp"
#include "Menu.hpp"
#include "MenuObject.hpp"
#include "Music.hpp"
#include "Window.hpp"
#include "Play.hpp"

class GameLoop
{
public:
	GameLoop();
	~GameLoop();

	void run();
	void nextLevel();
	void processEvents(float deltaTime, sf::View cameraView);
	void update(float deltaTime);
	void render();
	void loader();

private:
	unsigned int level;
	bool isMousePressed;
	bool isMenu;
	bool loadOnce; // This is to avoid changing for each lap of the loop

	// Ordre de declaration importante car si _window et _music sont pas declare avant _menu alors 
	// il ne seront pas initilalié lorsquon les met en parametre de _menu

	GameStatistics _gameStatistics;
	Window_s _window;
	Music _music;
	Menu _menu;
	Play _play;
	
};
