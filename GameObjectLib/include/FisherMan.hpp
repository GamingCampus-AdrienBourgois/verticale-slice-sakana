#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"

class FicherMan {
	PlayObject& _obj;
	sf::View cameraView;



public:
	enum Fishing
	{
		HOOK,
		BAR
	};

	FicherMan(PlayObject& obj) : _obj(obj) {

	}

	void load(Window_s& window) {
		sf::Vector2u windowSize = window.getWindow().getSize();
		float X = static_cast<float>(windowSize.x);
		float Y = static_cast<float>(windowSize.y);

		cameraView.setSize(static_cast<float>(window.getWindow().getSize().x), static_cast<float>(window.getWindow().getSize().y));
		cameraView.setCenter(_obj.globalSprt[GlobalS::HFISH].getPosition().x, _obj.globalSprt[GlobalS::HFISH].getPosition().y);


		// Load Map
		if (!_obj.bgTex[BackS::MAP].loadFromFile("asset/sprite/fishgame/fisherman/map.png")) {
			throw std::runtime_error("Failed to load");
		}
		_obj.bgSprt[Fishing::HOOK].setTexture(_obj.bgTex[BackS::MAP]);
		_obj.bgSprt[Fishing::HOOK].setScale(5.f, 5.f);

		// Load sprites
		if (!_obj.globalTex[Fishing::HOOK].loadFromFile("asset/sprite/fishgame/fisherman/hook.png")) {
			throw std::runtime_error("Failed to load");
		}


		_obj.globalSprt[Fishing::HOOK].setTexture(_obj.globalTex[Fishing::HOOK]);
		_obj.globalSprt[Fishing::HOOK].setScale(0.2f, 0.2f);
		_obj.globalSprt[Fishing::HOOK].setOrigin(_obj.globalTex[Fishing::HOOK].getSize().x / 2.f, _obj.globalTex[Fishing::HOOK].getSize().y / 2.f);

		_obj.globalSprt[Fishing::HOOK].setPosition(sf::Vector2f(X / 2, Y / 2));



	}


	void animate(float deltaTime, Window_s& window) {

	}
	void handleEvent(const sf::Event& event, Window_s& window, Music& music) {

	}

	void followMouse(Window_s& window, float deltaTime) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
		sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);



		sf::Vector2f currentPosition = _obj.globalSprt[Fishing::HOOK].getPosition();


		sf::Vector2f newPosition = currentPosition + deltaTime * (mousePosF - currentPosition);

		_obj.globalSprt[Fishing::HOOK].setPosition(newPosition);

		cameraView.setCenter(newPosition);

		window.getWindow().setView(cameraView);
	}
};