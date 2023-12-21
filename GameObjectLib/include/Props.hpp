#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include <random>

#define _CAN_ 50
#define _WOOD_ 50
#define _TRASH1_ 50
#define _TRASH2_ 50
#define _ALGAE_ 100



class Props {
	PlayObject& _obj;
	float elapsed;
	int frame;

	bool fishingRodActive;
	bool fishingRodDescending;
	float fishingRodSpeed;
	float fishingRodMaxY;
	float fishingRodMinY;


	std::mt19937 gen;
	std::random_device rd;

	std::map<size_t, float> obstacleDelays;
	size_t nextObstacleId = 0;

	int can;
	int wood;
	int trash1;
	int trash2;
	int algae;



public:


	Props(PlayObject& obj) : _obj(obj), gen(rd()) {

		can = _CAN_;
		wood = _WOOD_;
		trash1 = _TRASH1_;
		trash2 = _TRASH2_;
		algae = _ALGAE_;

		frame = 0;
		elapsed = 0;

		fishingRodActive = false;
		fishingRodDescending = true;
		fishingRodSpeed = 1000.0f;
		fishingRodMaxY = 0.f;
		fishingRodMinY = 0.f;

	}
	void textureSetters(Window_s& window) {

		if (!_obj.globalTex[GlobalS::ALGAE].loadFromFile("asset/sprite/fishgame/algae.png")) {
			throw std::runtime_error("Failed to load texture");
		}
		if (!_obj.globalTex[GlobalS::CAN].loadFromFile("asset/sprite/fishgame/Wood Plank.png")) {
			throw std::runtime_error("Failed to load texture");
		}
		if (!_obj.globalTex[GlobalS::WOOD].loadFromFile("asset/sprite/fishgame/Plastic bag.png")) {
			throw std::runtime_error("Failed to load texture");
		}
		if (!_obj.globalTex[GlobalS::TRASH1].loadFromFile("asset/sprite/fishgame/Cannette .png")) {
			throw std::runtime_error("Failed to load texture");
		}
		if (!_obj.globalTex[GlobalS::TRASH2].loadFromFile("asset/sprite/fishgame/Plastic bag 2.png")) {
			throw std::runtime_error("Failed to load texture");
		}
		if (!_obj.globalTex[GlobalS::HOOK].loadFromFile("asset/sprite/fishgame/hook.png")) {
			throw std::runtime_error("Failed to load hook texture");
		}

		_obj.globalSprt[GlobalS::HOOK].setTexture(_obj.globalTex[GlobalS::HOOK]);
		_obj.globalSprt[GlobalS::HOOK].setScale(sf::Vector2f(2.f, 2.f));
		sf::Vector2f spriteSize = sf::Vector2f(_obj.globalSprt[GlobalS::HOOK].getLocalBounds().width, 0);
		_obj.globalSprt[GlobalS::HOOK].setOrigin(spriteSize * 0.5f);


		_obj.globalRec[RectS::FISHLINE].setSize(sf::Vector2f(75, 0)); // Width of 5 and dynamic height
		_obj.globalRec[RectS::FISHLINE].setFillColor(sf::Color::Black); // Line color

	}

	void animateFishingRod(float deltaTime, Window_s& window) {
		if (fishingRodActive) {
			float newY;
			if (fishingRodDescending) {
				// Move down
				newY = _obj.globalRec[RectS::FISHLINE].getSize().y + (fishingRodSpeed * deltaTime);
				if (newY >= fishingRodMaxY) {
					fishingRodDescending = false; // Start moving up once the maximum depth is reached

					fishingRodMaxY = _obj.globalSprt[GlobalS::HFISH].getPosition().y;
				}
			}
			else {
				// Move up
				newY = _obj.globalRec[RectS::FISHLINE].getSize().y - (fishingRodSpeed * deltaTime);
				if (newY <= fishingRodMinY) {
					fishingRodActive = false; // Deactivate and reset once it reaches the surface
					fishingRodDescending = true; // Reset for the next descent
				}
			}
			_obj.globalRec[RectS::FISHLINE].setSize(sf::Vector2f(5, newY));
			_obj.globalSprt[GlobalS::HOOK].setPosition(_obj.globalSprt[GlobalS::HOOK].getPosition().x, newY);

			// Check for collision with fish
			if (_obj.globalSprt[GlobalS::HOOK].getGlobalBounds().intersects(_obj.globalSprt[GlobalS::HFISH].getGlobalBounds())) {
				// Handle fish caught
				fishingRodActive = false; // Deactivate fishing rod
			}
		}
		else {
			// Activate the fishing rod at the fish's X position
			sf::Vector2f fishPos = _obj.globalSprt[GlobalS::HFISH].getPosition();
			_obj.globalRec[RectS::FISHLINE].setPosition(fishPos.x, fishingRodMinY);
			_obj.globalSprt[GlobalS::HOOK].setPosition(fishPos.x, fishingRodMinY);
			_obj.globalRec[RectS::FISHLINE].setSize(sf::Vector2f(5, 0));
			fishingRodActive = true;
			fishingRodDescending = true; // Start by moving downwards
		}
	}


	void animateSpecificObstacle(float deltaTime, std::vector<sf::Sprite>& obstacles, Window_s& window) {
		std::random_device rd;
		std::mt19937 gen(rd());
		float maxY = (_obj.bgSprt[BackS::MAP].getScale().y * _obj.bgTex[BackS::MAP].getSize().y);
		std::uniform_real_distribution<> disY(100, maxY - 50); // Y position

		
		for (size_t i = 0; i < obstacles.size(); ++i) {

			float& delay = obstacleDelays[i];
			if (delay > 0) {
				// Decrease the delay and skip this obstacle if the delay hasn't elapsed
				delay -= deltaTime;
			}
			else {
				float yPos = obstacles[i].getPosition().y;
				float rotationSpeed = calculateRotationSpeed(yPos, maxY);
				float moveSpeed = calculateMoveSpeed(yPos, maxY);

				// Update rotation
				obstacles[i].rotate(rotationSpeed * deltaTime);

				// Move obstacle left
				obstacles[i].move(-deltaTime * moveSpeed, 0);

				// Check if off-screen
				if (obstacles[i].getPosition().x + obstacles[i].getGlobalBounds().width < 0) {
					// Reset position to the right with a new random Y position
					obstacles[i].setPosition((_obj.bgSprt[BackS::MAP].getScale().x * _obj.bgTex[BackS::MAP].getSize().x) + 50, disY(gen));
				}
			}

		}



	}

	float calculateRotationSpeed(float yPos, float maxY) {
		return 360.0f / (1.0f + 9.0f * (maxY - yPos) / maxY);
	}

	float calculateMoveSpeed(float yPos, float maxY) {
		return 40.0f + 760.0f * yPos / maxY;
	}

	void generateAlgae(Window_s& window, int count) {
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<> disX(50, _obj.bgSprt[BackS::MAP].getScale().x * _obj.bgTex[BackS::MAP].getSize().x);
		std::uniform_real_distribution<> disY(200, _obj.bgSprt[BackS::MAP].getScale().y * _obj.bgTex[BackS::MAP].getSize().y);
		std::uniform_real_distribution<> disAngle(0, 360); // Angle entre 0 et 360 degr�s



		for (int i = 0; i < count; i++) {
			sf::Sprite algaeSprite;
			algaeSprite.setTexture(_obj.globalTex[GlobalS::ALGAE]);
			algaeSprite.setPosition(disX(gen), disY(gen));
			algaeSprite.setRotation(disAngle(gen)); // D�finir une rotation al�atoire
			_obj.massSprt[MassS::ALGAES].push_back(algaeSprite);
		}
	}

	void generateObstacles(Window_s& window, int count, GlobalS textureId, MassS spriteId) {
		std::uniform_real_distribution<> disY(100, (_obj.bgSprt[BackS::MAP].getScale().y * _obj.bgTex[BackS::MAP].getSize().y) + 50);
		std::uniform_real_distribution<> disDelay(0, 100);

		for (int i = 0; i < count; i++) {
			sf::Sprite obs;
			obs.setTexture(_obj.globalTex[textureId]);
			obs.setPosition(sf::Vector2f(_obj.bgSprt[BackS::MAP].getScale().x * _obj.bgTex[BackS::MAP].getSize().x, disY(gen)));
			_obj.massSprt[spriteId].push_back(obs);
			obstacleDelays[nextObstacleId] = disDelay(gen);
			nextObstacleId++;
		}
	}



	void load(Window_s& window) {
		textureSetters(window);
		generateAlgae(window, algae);

		generateObstacles(window, can, GlobalS::CAN, MassS::CANS);
		generateObstacles(window, wood, GlobalS::WOOD, MassS::WOODS);
		generateObstacles(window, trash1, GlobalS::TRASH1, MassS::TRASHS1);
		generateObstacles(window, trash2, GlobalS::TRASH2, MassS::TRASHS2);



	}



	void animate(float deltaTime, Window_s& window) {
		animateAlgae(deltaTime, window);
		animateSpecificObstacle(deltaTime, _obj.massSprt[MassS::CANS], window);
		animateSpecificObstacle(deltaTime, _obj.massSprt[MassS::WOODS], window);
		animateSpecificObstacle(deltaTime, _obj.massSprt[MassS::TRASHS1], window);
		animateSpecificObstacle(deltaTime, _obj.massSprt[MassS::TRASHS2], window);

		animateFishingRod(deltaTime, window);


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
	
	int getCan() const {
		return can;
	}

	void setCan(int value) {
		can = value;
	}

	int getWood() const {
		return wood;
	}

	void setWood(int value) {
		wood = value;
	}

	int getTrash1() const {
		return trash1;
	}

	void setTrash1(int value) {
		trash1 = value;
	}

	int getTrash2() const {
		return trash2;
	}

	void setTrash2(int value) {
		trash2 = value;
	}

	int getAlgae() const {

		return algae;
	}

	void setAlgae(int value) {
		algae = value;
	}
};
