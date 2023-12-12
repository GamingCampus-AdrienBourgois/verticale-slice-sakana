#include "GameLoop.hpp"

GameLoop::GameLoop() : isMousePressed(false), _gameStatistics(), _window(static_cast<std::string>("Sakana Man")), _menu(_window, _music)
{
	// Set level to first
	isMenu = true;
	level = 0;

	// Load menu
	_menu.load(_window);
	// Base Menu draw
	_menu.draw(_window);

	// Load music for each level
	_music.loadMusic();
	// Music player and level 0 = menu music
	_music.playMusic(0);

	// Load states for all game (set them)
	_gameStatistics.loadStatistics();
	_gameStatistics.incrementGameStarts();
}

GameLoop::~GameLoop()
{
	_gameStatistics.saveStatistics();
}

void GameLoop::run()
{
	sf::Clock clock;
	sf::View cameraView;

	while (_window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		processEvents(deltaTime, cameraView);
		update(deltaTime);
		nextLevel();
		render();
	}
}

void GameLoop::processEvents(float deltaTime, sf::View cameraView)
{
	sf::Event event;



	while (_window.pollEvent(event))
	{


		switch (event.type)
		{
		case sf::Event::Closed: _window.close();
			break;
		case sf::Event::KeyPressed: 
			if (event.key.code == sf::Keyboard::Escape)
			{
				_window.close();
			}


			if (event.key.code == sf::Keyboard::Return && _menu.getMenuState() == 1) // 1 = play state and 0 = menu 
			{
				_menu.togglePlayMenu();
				
			}
			break;
		case sf::Event::MouseButtonPressed: isMousePressed = true;
			break;
		case sf::Event::MouseButtonReleased: if (isMousePressed)
			{
				_gameStatistics.incrementClicks();
				_gameStatistics.saveStatistics();
				isMousePressed = false;
			}
			break;
		case sf::Event::Resized: 
			sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
			_window.getWindow().setView(sf::View(visibleArea));

			if (isMenu)
				_menu.reloadByState(_window);
			else
			{
				// game resizer
			}
			break;
		}





		if (isMenu)
			_menu.handleEvent(event, _window, _music);
		else
		{
			//game events
		}
	}
	isMenu = (_menu.getMenuState() == 1 ? false : true);
}

void GameLoop::nextLevel()
{
	if (/*next level cond*/true != true)
	{
		_music.stopMusic(level);
		if (/*level not max*/true != true)
		{
			level += 1;
			_music.playMusic(level);
		}
		else
		{
			level = 0;
			_music.playMusic(level);
		}
	}
}

void GameLoop::update(float deltaTime)
{
	if (isMenu)
		_menu.update(_window, _music, deltaTime);
	else
	{
		// game updates
	}


	_gameStatistics.updateGameTime(deltaTime);
}

void GameLoop::render()
{
	_window.clear();
	_window.renderLayers();
	_window.display();
}
