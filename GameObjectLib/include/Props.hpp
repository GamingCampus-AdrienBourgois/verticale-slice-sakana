#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include <random>

#define _CAN_ 50
#define _WOOD_ 50
#define _TRASH1_ 50
#define _TRASH2_ 50
#define _ALGAE_ 50



class Props {
	PlayObject& _obj;
	float elapsed;
	int frame;

	//sf::Sprite& hfish;




	std::map<size_t, float> obstacleDelays;
	size_t nextObstacleId = 0;

	int can;
	int wood;
	int trash1;
	int trash2;
	int algae;

public:


	Props(PlayObject& obj) : _obj(obj) {

		can = _CAN_;
		wood = _WOOD_;
		trash1 = _TRASH1_;
		trash2 = _TRASH2_;
		algae = _ALGAE_;

		frame = 0;
		elapsed = 0;
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
		std::cout << "tess";

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> disY(100, (_obj.bgSprt[BackS::MAP].getScale().y * _obj.bgTex[BackS::MAP].getSize().y) + 50); // Y position
		std::uniform_real_distribution<> disDelay(0, 100); // Delay time in seconds



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
