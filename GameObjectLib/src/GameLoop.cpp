#include "GameLoop.hpp"

GameLoop::GameLoop() : 
isMousePressed(false),
loadOnce(true),
isMenu(true),
level(0),
_play(),
_gameStatistics(), 
_window(static_cast<std::string>("Sakana Man")), 
_menu(_window, _music)
{

}

GameLoop::~GameLoop()
{
	_gameStatistics.saveStatistics();
}

void GameLoop::loader() 
{
	if (loadOnce) {

		// Load menu and Base Menu draw
		_menu.load(_window);
		_menu.draw(_window);

		// Load music for each level and Music player, level 0 = base menu music
		_music.loadMusic();
		_music.playMusic(0);

		// Load states for all game (set them)
		_gameStatistics.loadStatistics();
		_gameStatistics.incrementGameStarts();
	}

	// Manage menu change to game for game loader to load once (when the state is changed)
	bool initialIsMenu = isMenu;
	isMenu = (_menu.getMenuState() == 1 ? false : true);
	bool changedIsMenu = false;
	if (initialIsMenu) {
		changedIsMenu = isMenu ^ initialIsMenu; // bitwise operation 0 ^ 0 = 1 && 1 ^ 1 = 1
	}
	if (changedIsMenu) {
		_play.load(_window);
		_play.draw(_window);
	}

	loadOnce &= false; // bitwise operation (if its true [1] its set to false [0] and if its true do nothing)
}

void GameLoop::run()
{
	sf::Clock clock;
	sf::View cameraView;

	while (_window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		loader();
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
				_window.close();
			if (event.key.code == sf::Keyboard::Return && _menu.getMenuState() == 1) { // 1 = play state and 0 = menu 
				_menu.togglePlayMenu();
			}

			break;
		case sf::Event::MouseButtonPressed: 
			isMousePressed = true;
			break;
		case sf::Event::MouseButtonReleased: 
			if (isMousePressed)
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

				
			break;
		}

		if (isMenu)
			_menu.handleEvent(event, _window, _music);
		else
			_play.handleEvent(event, _window, _music);

	}

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
		_play.update(_window, _music, deltaTime);


	_gameStatistics.updateGameTime(deltaTime);
}

void GameLoop::render()
{
	_window.clear();
	_window.renderLayers();
	_window.display();
}
