#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"

class FicherMan {
	PlayObject& _obj;
	sf::View cameraView;
	float elapsed;
	float elapsedAnim;
	float elapsedF = 0;
	float elapsedFA = 0;
	float elapsedA = 0;
	int currentFrame;
	int currentFrameFish = 0;
	int timerAnim = 0;
	int stateAnim = 0;
	bool isFishing;
	bool isAnimating;
	int nbFish;
	float alpha;
	const float radius = 250.0f; // Rayon du demi-cercle
	const sf::Vector2f center = sf::Vector2f(757.0f, -311.0f); // Centre du demi-cercle
	const float angularSpeed = 1.0f; // Vitesse angulaire en radians par seconde


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
		currentFrame = 0;
		elapsed = 0.f;
		elapsedAnim = 0.f;
		isFishing = true;
		isAnimating = false;
		nbFish = 0;
		alpha = 0.f;
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
		_obj.bgSprt[BackS::SKY].setScale(4.f, 3.f);
		_obj.bgSprt[BackS::SKY].setPosition(sf::Vector2f(-1472.f, -687.f));

		_obj.bgSprt[GlobalS::HOOK].setTexture(_obj.bgTex[BackS::MAP]);
		_obj.bgSprt[GlobalS::HOOK].setScale(5.f, 5.f);
		_obj.bgSprt[GlobalS::HOOK].setPosition(sf::Vector2f(-1472.f, 0.f));

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

		if (!_obj.globalTex[GlobalS::HOUSE].loadFromFile("asset/sprite/fishgame/FishingPart.png")) {
			throw std::runtime_error("Failed to load");
		}

		if (!_obj.globalTex[GlobalS::FISHERMAN].loadFromFile("asset/sprite/fishgame/Fish_Anim_start.png")) {
			throw std::runtime_error("Failed to load");
		}

		_obj.globalSprt[GlobalS::FISHERMAN].setTexture(_obj.globalTex[GlobalS::FISHERMAN]);
		_obj.globalSprt[GlobalS::FISHERMAN].setScale(4.f, 4.f);
		_obj.globalSprt[GlobalS::FISHERMAN].setPosition(sf::Vector2f(487.f, -391.f));

		_obj.globalSprt[GlobalS::HOUSE].setTexture(_obj.globalTex[GlobalS::HOUSE]);
		_obj.globalSprt[GlobalS::HOUSE].setScale(2.f, 2.f);
		_obj.globalSprt[GlobalS::HOUSE].setPosition(sf::Vector2f(-1472.f, -640.f));

		_obj.globalSprt[GlobalS::FISHA].setTexture(_obj.globalTex[GlobalS::FISHA]);
		_obj.globalSprt[GlobalS::FISHA].setPosition(sf::Vector2f(600.f, 1200.f));
		_obj.globalSprt[GlobalS::FISHB].setTexture(_obj.globalTex[GlobalS::FISHB]);
		_obj.globalSprt[GlobalS::FISHB].setPosition(sf::Vector2f(1200.f, 800.f));
		_obj.globalSprt[GlobalS::FISHC].setTexture(_obj.globalTex[GlobalS::FISHC]);
		_obj.globalSprt[GlobalS::FISHC].setPosition(sf::Vector2f(1800.f, 1400.f));
		_obj.globalSprt[GlobalS::FISHD].setTexture(_obj.globalTex[GlobalS::FISHD]);
		_obj.globalSprt[GlobalS::FISHD].setPosition(sf::Vector2f(2200.f, 1200.f));
		for (size_t i = GlobalS::FISHA; i < GlobalS::GEND; i++)
		{
			_obj.globalSprt[i].setScale(2.f, 2.f);
		}

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
		if (nbFish < 4) {
			animateFisherman(deltaTime, window);
			displayLine();
		}
		else {
			animateDeath(deltaTime, window);
		}
	}

	void animateDeath(float deltaTime, Window_s& window) {
		isFishing = false;
		sf::RectangleShape blackoutRect(sf::Vector2f(10000, 10000));
		blackoutRect.setFillColor(sf::Color(0, 0, 0, 0));
		blackoutRect.setPosition(-2000, -2000);

		if (alpha < 255.0f) {
			alpha += 5.0f;
			blackoutRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(alpha)));
			_obj.globalRec[RectangleS::TRANS] = blackoutRect;
			currentFrame = 0;
			timerAnim = 0;
		}
		else {
			_obj.globalRec[RectangleS::BAR].setPosition(20000.f, 20000.f);
			_obj.globalSprt[GlobalS::HOOK].setPosition(20000.f, 20000.f);
			_obj.globalSprt[GlobalS::FISHERMAN].setPosition(20000.f, 20000.f);

			elapsedAnim += deltaTime;
			isAnimating = true;

			if (!_obj.globalTex[GlobalS::FISHERMAND].loadFromFile("asset/sprite/fishgame/Fall_anim.png")) {
				throw std::runtime_error("Failed to load");
			}
			_obj.globalSprt[GlobalS::FISHERMAND].setTexture(_obj.globalTex[GlobalS::FISHERMAND]);
			_obj.globalSprt[GlobalS::FISHERMAND].setScale(4.f, 4.f);
			_obj.globalSprt[GlobalS::FISHERMAND].setPosition(sf::Vector2f(487.f, -391.f));

			if (elapsedAnim >= 0.50f && stateAnim == 0) {
				_obj.globalSprt[GlobalS::FISHERMAND].setPosition(sf::Vector2f(487.f, -381.f));
				stateAnim++;
				elapsedAnim -= 0.50f;
			}

			if (elapsedAnim >= 0.50f && stateAnim == 1) {
				_obj.globalSprt[GlobalS::FISHERMAND].setPosition(sf::Vector2f(487.f, -391.f));
				stateAnim++;
				elapsedAnim -= 0.50f;
			}

			if (elapsedAnim >= 0.50f && stateAnim == 2) {
				_obj.globalSprt[GlobalS::FISHERMAND].setPosition(sf::Vector2f(487.f, -381.f));
				stateAnim++;
				elapsedAnim -= 0.50f;
			}

			if (elapsedAnim >= 0.50f && stateAnim == 3) {
				_obj.globalSprt[GlobalS::FISHERMAND].setPosition(sf::Vector2f(487.f, -391.f));
				stateAnim++;
				elapsedAnim -= 0.50f;
			}

			if (elapsedAnim >= 0.30f && timerAnim <= 3 && stateAnim >= 4 && stateAnim < 8) {
				currentFrame = (currentFrame + 1) % 5;
				elapsedAnim -= 0.30f;
				std::cout << "framed";
				timerAnim++;
				stateAnim++;
			}

			if (stateAnim >= 8) {
				animateLastFish(deltaTime, window);
				sf::Vector2f newCenter = sf::Vector2f(_obj.globalSprt[GlobalS::FISHERMANS].getPosition().x, _obj.globalSprt[GlobalS::FISHERMANS].getPosition().y);
				cameraView.setCenter(newCenter);
				window.getWindow().setView(cameraView);
			}

			_obj.globalSprt[GlobalS::FISHERMAND].setTextureRect(sf::IntRect(currentFrame * static_cast<int>(FRAME_WIDTH), 0, static_cast<int>(FRAME_WIDTH), static_cast<int>(FRAME_HEIGHT)));

			_obj.globalRec[RectangleS::TRANS] = blackoutRect;
			if (stateAnim < 8) {
				sf::Vector2f newCenter = sf::Vector2f(_obj.globalSprt[GlobalS::FISHERMAND].getPosition().x + 100, _obj.globalSprt[GlobalS::FISHERMAND].getPosition().y + 250);
				cameraView.setCenter(newCenter);
				window.getWindow().setView(cameraView);
			}
		}
	}

	void animateLastFish(float deltaTime, Window_s& window) {
		if (!_obj.globalTex[GlobalS::FISHERMANS].loadFromFile("asset/sprite/fishgame/fishs/HumanFish.png")) {
			throw std::runtime_error("Failed to load");
		}

		_obj.globalSprt[GlobalS::FISHERMANS].setTexture(_obj.globalTex[GlobalS::FISHERMANS]);
		_obj.globalSprt[GlobalS::FISHERMANS].setScale(4.f, 4.f);

		// Mettez à jour l'angle en fonction du temps
		elapsedF += deltaTime;

		if (elapsedF <= 3.f) {
			
			_obj.globalSprt[GlobalS::FISHERMANS].setPosition(sf::Vector2f(487.f, -391.f));
			float angle = angularSpeed * elapsedF;

			// Calculez la nouvelle position du sprite sur le demi-cercle
			float x = center.x - radius * std::cos(angle);
			float y = center.y - radius * std::sin(angle);

			// Mettez à jour la position du sprite
			_obj.globalSprt[GlobalS::FISHERMANS].setPosition(x, y);
		}
		else if (elapsedF >= 3.f) {
			_obj.globalSprt[GlobalS::FISHERMANS].move(0, 1);
		}
	}

	void animateFisherman(float deltaTime, Window_s& window) {
		sf::Vector2f spritePos = _obj.globalSprt[GlobalS::FISHERMAN].getPosition();
		elapsed += deltaTime;
		elapsedFA += deltaTime;
		if (elapsed >= 0.30f && timerAnim <=3) {
			currentFrame = (currentFrame + 1) % 5;
			elapsed -= 0.30f;
			std::cout << "framed";
			timerAnim++;
		}
		_obj.globalSprt[GlobalS::FISHERMAN].setTextureRect(sf::IntRect(currentFrame * static_cast<int>(FRAME_WIDTH), 0, static_cast<int>(FRAME_WIDTH), static_cast<int>(FRAME_HEIGHT)));

		if (elapsedFA >= 0.15f) {
			currentFrameFish = (currentFrameFish + 1) % 2;
			elapsedFA -= 0.15f;
		}
		_obj.globalSprt[GlobalS::FISHA].setTextureRect(sf::IntRect(currentFrameFish * 48, 0, 48, 30));
		_obj.globalSprt[GlobalS::FISHB].setTextureRect(sf::IntRect(currentFrameFish * 45, 0, 45, 31));
		_obj.globalSprt[GlobalS::FISHC].setTextureRect(sf::IntRect(currentFrameFish * 78, 0, 78, 24));
		_obj.globalSprt[GlobalS::FISHD].setTextureRect(sf::IntRect(currentFrameFish * 31, 0, 31, 34));
		_obj.globalSprt[GlobalS::FISHERMANS].setTextureRect(sf::IntRect(currentFrameFish * 29, 0, 29, 21));
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
		sf::Vector2f pointInitial(735.f, 0.f); // Define your initial point for the hook

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
		sf::Vector2f pointA(735.f, -260.f);
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

			if (!isAnimating) {
				cameraView.setCenter(newPosition);
				window.getWindow().setView(cameraView);
			}
		}
	}

	void update(const float deltaTime, Window_s &window) {
		collision(deltaTime, window);
	}
};