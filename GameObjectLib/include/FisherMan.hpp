#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"

class FicherMan {
	PlayObject& _obj;
	sf::View cameraView;
	float elapsed;
	int currentFrame;
	int timerAnim = 0;
	bool isFishing;
	int nbFish;

	static constexpr float FRAME_WIDTH = 64.f;
	static constexpr float FRAME_HEIGHT = 64.f;
	static constexpr float M_PI = 3.1416f;

public:
	enum Fishing
	{
		HOOK,
		BAR
	};

	FicherMan(PlayObject& obj) : _obj(obj) {
		currentFrame = 1;
		elapsed = 0.f;
		isFishing = true;
		nbFish = 0;
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

		if (!_obj.bgTex[BackS::SKY].loadFromFile("asset/sprite/fishgame/fisherman/WideBackground.png")) {
			throw std::runtime_error("Failed to load");
		}

		_obj.bgSprt[BackS::SKY].setTexture(_obj.bgTex[BackS::SKY]);
		_obj.bgSprt[BackS::SKY].setScale(3.f, 3.f);
		_obj.bgSprt[BackS::SKY].setPosition(sf::Vector2f(0.f, -687.f));

		_obj.bgSprt[GlobalS::HOOK].setTexture(_obj.bgTex[BackS::MAP]);
		_obj.bgSprt[GlobalS::HOOK].setScale(5.f, 5.f);

		// Load sprites
		if (!_obj.globalTex[GlobalS::HOOK].loadFromFile("asset/sprite/fishgame/fisherman/hook.png")) {
			throw std::runtime_error("Failed to load");
		}

		if (!_obj.globalTex[GlobalS::FISHA].loadFromFile("asset/sprite/fishgame/fishs/fish (1).png")) {
			throw std::runtime_error("Failed to load");
		}

		if (!_obj.globalTex[GlobalS::FISHB].loadFromFile("asset/sprite/fishgame/fishs/fish (2).png")) {
			throw std::runtime_error("Failed to load");
		}

		if (!_obj.globalTex[GlobalS::FISHC].loadFromFile("asset/sprite/fishgame/fishs/fish (3).png")) {
			throw std::runtime_error("Failed to load");
		}

		if (!_obj.globalTex[GlobalS::FISHD].loadFromFile("asset/sprite/fishgame/fishs/fish (4).png")) {
			throw std::runtime_error("Failed to load");
		}

		if (!_obj.globalTex[GlobalS::HOUSE].loadFromFile("asset/sprite/fishgame/fisherHouse.png")) {
			throw std::runtime_error("Failed to load");
		}

		if (!_obj.globalTex[GlobalS::FISHERMAN].loadFromFile("asset/sprite/fishgame/Fish_Anim_start.png")) {
			throw std::runtime_error("Failed to load");
		}

		_obj.globalSprt[GlobalS::FISHERMAN].setTexture(_obj.globalTex[GlobalS::FISHERMAN]);
		_obj.globalSprt[GlobalS::FISHERMAN].setScale(2.f, 2.f);
		_obj.globalSprt[GlobalS::FISHERMAN].setPosition(sf::Vector2f(487.f, -196.f));

		_obj.globalSprt[GlobalS::HOUSE].setTexture(_obj.globalTex[GlobalS::HOUSE]);
		_obj.globalSprt[GlobalS::HOUSE].setScale(2.f, 2.f);
		_obj.globalSprt[GlobalS::HOUSE].setPosition(sf::Vector2f(0.f, -262.f));

		_obj.globalSprt[GlobalS::FISHA].setTexture(_obj.globalTex[GlobalS::FISHA]);
		_obj.globalSprt[GlobalS::FISHA].setPosition(sf::Vector2f(600.f, 1200.f));
		_obj.globalSprt[GlobalS::FISHB].setTexture(_obj.globalTex[GlobalS::FISHB]);
		_obj.globalSprt[GlobalS::FISHB].setPosition(sf::Vector2f(1200.f, 800.f));
		_obj.globalSprt[GlobalS::FISHC].setTexture(_obj.globalTex[GlobalS::FISHC]);
		_obj.globalSprt[GlobalS::FISHC].setPosition(sf::Vector2f(1800.f, 1400.f));
		_obj.globalSprt[GlobalS::FISHD].setTexture(_obj.globalTex[GlobalS::FISHD]);
		_obj.globalSprt[GlobalS::FISHD].setPosition(sf::Vector2f(2200.f, 1200.f));

		_obj.globalSprt[GlobalS::HOOK].setTexture(_obj.globalTex[GlobalS::HOOK]);
		_obj.globalSprt[GlobalS::HOOK].setScale(1.f, 1.f);
		_obj.globalSprt[GlobalS::HOOK].setOrigin(_obj.globalTex[GlobalS::HOOK].getSize().x / 2.f, _obj.globalTex[GlobalS::HOOK].getSize().y / 2.f);

		_obj.globalSprt[GlobalS::HOOK].setPosition(sf::Vector2f(X / 2, Y / 2));

		sf::Font font;
		if (!font.loadFromFile("asset/font/Beyonders.ttf")) {
			std::cout << "Problème de police";
		}

		_obj._fontAny = font;

		// Créer un objet texte
		sf::Text text;
		text.setFont(_obj._fontAny); // Sélectionner la police
		text.setString(std::to_string(nbFish) + " / 4"); // Définir le texte
		text.setCharacterSize(24); // Définir la taille du texte
		text.setPosition(-100.f, -100.f);
		text.setFillColor(sf::Color::Red); // Définir la couleur du texte
		_obj.globalTexts.push_back(text);
	}

	void animate(float deltaTime, Window_s& window) {

	}

	void animateFisherman(float deltaTime, Window_s& window) {
		sf::Vector2f spritePos = _obj.globalSprt[GlobalS::FISHERMAN].getPosition();
		elapsed += deltaTime;
		if (elapsed >= 0.30f && timerAnim <=7) {
			currentFrame = (currentFrame + 1) % 5;
			elapsed -= 0.30f;
			std::cout << "framed";
			timerAnim++;
		}
		_obj.globalSprt[GlobalS::FISHERMAN].setTextureRect(sf::IntRect(currentFrame * static_cast<int>(FRAME_WIDTH), 0, static_cast<int>(FRAME_WIDTH), static_cast<int>(FRAME_HEIGHT)));
	}

	void handleEvent(const sf::Event& event, Window_s& window, Music& music) {

	}

	void collision(const float deltaTime, Window_s &window) {
		bool proke = false;
		for (size_t i = GlobalS::FISHA; i < GlobalS::GEND; i++)
		{
			if (_obj.globalSprt[i].getGlobalBounds().intersects(_obj.globalSprt[GlobalS::HOOK].getGlobalBounds())) {
				remonte(deltaTime, i, window);
				proke = true;
			}
		}
			if (proke)
			{
				isFishing = false;
			}
			else
				isFishing = true; // Hook has returned, can fish again
		
	}

	void remonte(float deltaTime, size_t i, Window_s &window) {
		sf::Vector2f pointInitial(610.f, 0.f); // Define your initial point for the hook

		float vitesseRemontee = 400.f; // Speed of return (adjust as needed)

		sf::Vector2f currentPosition = _obj.globalSprt[GlobalS::HOOK].getPosition();
		sf::Vector2f direction = pointInitial - currentPosition;

		// Check if we are close enough to the initial point
		if (std::sqrt(direction.x * direction.x + direction.y * direction.y) < vitesseRemontee * deltaTime) {
			_obj.globalSprt[GlobalS::HOOK].move(direction);
			_obj.globalSprt[i].move(direction);

		}
		else {
			// Normalize the direction
			float norme = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			direction /= norme;

			// Calculate the movement based on speed and delta time
			sf::Vector2f deplacement = direction * vitesseRemontee * deltaTime;

			// Update the position of the hook and the fish (if caught)
			_obj.globalSprt[GlobalS::HOOK].move(deplacement);
			_obj.globalSprt[i].move(deplacement);
			_obj.globalTexts[0].setPosition(sf::Vector2f(currentPosition.x - 780.f, currentPosition.y - 430.f));
			cameraView.setCenter(currentPosition);
			window.getWindow().setView(cameraView);
		}
		if (_obj.globalSprt[GlobalS::HOOK].getPosition() == pointInitial) {
			std::cout << nbFish;
			window.removeFromRenderLayer(static_cast<int>(Scene::SPRITESGB), _obj.globalSprt[i]);
			_obj.globalSprt[i].setPosition(sf::Vector2f(20000.f, 20000.f));
			nbFish += 1;
			_obj.globalTexts[0].setString(std::to_string(nbFish) + " / 4");
		}
	}


	void displayLine() {
		sf::Vector2f pointA(610.f, -130.f);
		sf::Vector2f pointB(_obj.globalSprt[GlobalS::HOOK].getPosition().x, _obj.globalSprt[GlobalS::HOOK].getPosition().y - 30.f);

		// Calcul de la distance entre les points A et B
		float distance = std::sqrt((pointB.x - pointA.x) * (pointB.x - pointA.x) +
			(pointB.y - pointA.y) * (pointB.y - pointA.y));

		// Création d'un rectangle pour représenter la ligne
		sf::RectangleShape line(sf::Vector2f(distance, 4.f)); // 4.f est l'épaisseur de la ligne

		// Positionnement du rectangle
		line.setPosition(pointA);

		// Calcul de la rotation pour aligner la ligne avec les points A et B
		float angle = std::atan2(pointB.y - pointA.y, pointB.x - pointA.x) * (180.f / M_PI);
		line.setRotation(angle);

		// Choix de la couleur de la ligne
		line.setFillColor(sf::Color(145, 92, 67));

		_obj.globalRec[RectangleS::BAR] = line;
	}

	void followMouse(Window_s& window, float deltaTime) {
		if (isFishing) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
			sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);



			sf::Vector2f currentPosition = _obj.globalSprt[GlobalS::HOOK].getPosition();


			sf::Vector2f newPosition = currentPosition + deltaTime * (mousePosF - currentPosition);

			_obj.globalSprt[GlobalS::HOOK].setPosition(newPosition);
			_obj.globalTexts[0].setPosition(sf::Vector2f(newPosition.x -780.f, newPosition.y - 430.f));

			cameraView.setCenter(newPosition);

			window.getWindow().setView(cameraView);
		}
	}

	void update(const float deltaTime, Window_s &window) {
		collision(deltaTime, window);
	}
};