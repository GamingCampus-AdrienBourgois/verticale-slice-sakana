#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include <random>

class Props {
	PlayObject& _obj;
	float elapsed;
	int frame;
	int nbrAlgae;

public:


	Props(PlayObject& obj) : _obj(obj) {
		nbrAlgae = 50;
		frame = 0;
		elapsed = 0;
	}
	void textureSetters(Window_s& window) {
		std::vector<std::string> globaleFile = {};

		if (!_obj.globalTex[GlobalS::ALGAE].loadFromFile("asset/sprite/fishgame/algae.png")) {
			throw std::runtime_error("Failed to load texture");
		}

		for (size_t i = 0; i < globaleFile.size(); i++) {
			if (!_obj.globalTex[i].loadFromFile(globaleFile[i])) {
				throw std::runtime_error("Failed to load texture");
			}
			else {
				_obj.globalSprt[i].setTexture(_obj.globalTex[i]);
			}
		}

	}

	void generateAlgae(Window_s& window, int count) {
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<> disX(50, _obj.bgSprt[BackS::MAP].getScale().x * _obj.bgTex[BackS::MAP].getSize().x);
		std::uniform_real_distribution<> disY(50, _obj.bgSprt[BackS::MAP].getScale().y * _obj.bgTex[BackS::MAP].getSize().y);
		std::uniform_real_distribution<> disAngle(0, 360); // Angle entre 0 et 360 degrés

		for (int i = 0; i < count; i++) {
			sf::Sprite algaeSprite;
			algaeSprite.setTexture(_obj.globalTex[GlobalS::ALGAE]);
			algaeSprite.setPosition(disX(gen), disY(gen));
			algaeSprite.setRotation(disAngle(gen)); // Définir une rotation aléatoire
			_obj.massSprt[MassS::ALGAES].push_back(algaeSprite);
		}
	}


	void load(Window_s& window) {
		textureSetters(window);

		generateAlgae(window, nbrAlgae);
	}


	void animateAlgae(float deltaTime, Window_s& window) {
		elapsed += deltaTime;

		sf::Vector2f size = static_cast<sf::Vector2f>(_obj.globalTex[GlobalS::ALGAE].getSize());
		size.x /= 20;

		if (elapsed >= 0.1f) {
			frame = (frame + 1) % 20;

			for (auto& algaeSprite : _obj.massSprt[MassS::ALGAES]) {
				algaeSprite.setTextureRect(sf::IntRect(size.x * frame, 0, size.x, size.y));
			}

			elapsed -= 0.1f;
		}
	}
	void handleEvent(const sf::Event& event, Window_s& window, Music& music) {

	}

};