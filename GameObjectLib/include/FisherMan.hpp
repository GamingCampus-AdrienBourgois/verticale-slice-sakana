#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include <array>

class FicherMan {
	PlayObject& _obj;

	sf::View& cameraView;

	std::vector<int> power;


	// anim
	float elapsedFishing;
	int frameFishing;
	int count;

	bool returningToFisherman;
	sf::Vector2f returnPosition;
	bool fishCaught;
	size_t caughtFishIndex;

	sf::Vector2f lastUpdatedHookPosition;
	float timeSinceLastUpdate = 0.0f;

	bool isFishing;

	static constexpr float M_PI = 3.1416;
public:


	FicherMan(PlayObject& obj, sf::View& _cameraView) : _obj(obj), cameraView(_cameraView) {
		isFishing = true;
		returningToFisherman = false;
		fishCaught = false;
		caughtFishIndex = 0;
		frameFishing = 0;
		elapsedFishing = 0.f;
		count = 2;

	}

	const bool getIsFishing() const {
		return isFishing;
	}

	const std::vector<int> getPowers() const {
		return power;
	}

	void load(Window_s& window) {
		sf::Vector2u windowSize = window.getWindow().getSize();
		float X = static_cast<float>(windowSize.x);
		float Y = static_cast<float>(windowSize.y);



		if (!_obj.globalTex[GlobalS::HOUSE].loadFromFile("asset/sprite/fishgame/FishingPart.png")) {
			throw std::runtime_error("Failed to load");
		}
		if (!_obj.globalTex[GlobalS::FISHERMAN].loadFromFile("asset/sprite/fishgame/Fish_Anim_start.png")) {
			throw std::runtime_error("Failed to load");
		}
		if (!_obj.globalTex[GlobalS::FISHERMANH].loadFromFile("asset/sprite/fishgame/Hook_Anim.png")) {
			throw std::runtime_error("Failed to load");
		}
		if (!_obj.globalTex[GlobalS::FISHERMANS].loadFromFile("asset/sprite/fishgame/Fall_Anim.png")) {
			throw std::runtime_error("Failed to load");
		}
		if (!_obj.globalTex[GlobalS::FISHERMANF].loadFromFile("asset/sprite/fishgame/fishs/HumanFish.png")) {
			throw std::runtime_error("Failed to load");
		}




		_obj.globalSprt[GlobalS::FISHERMAN].setTexture(_obj.globalTex[GlobalS::FISHERMAN]);
		_obj.globalSprt[GlobalS::FISHERMAN].setScale(sf::Vector2f(7.f, 7.f));
		_obj.globalSprt[GlobalS::FISHERMAN].setPosition(sf::Vector2f((_obj.globalTex[GlobalS::HOUSE].getSize().x * 3.f) * 0.75f, (0.f - _obj.globalTex[GlobalS::HOUSE].getSize().y * 3.f) * 0.75f));

		_obj.globalSprt[GlobalS::HOUSE].setTexture(_obj.globalTex[GlobalS::HOUSE]);
		_obj.globalSprt[GlobalS::HOUSE].setScale(sf::Vector2f(3.f, 3.f));
		_obj.globalSprt[GlobalS::HOUSE].setPosition(sf::Vector2f(-10, 0.f - _obj.globalTex[GlobalS::HOUSE].getSize().y * 3.f));

		_obj.globalRec[RectS::TRANS].setSize(sf::Vector2f(1, 0));
		_obj.globalRec[RectS::TRANS].setFillColor(sf::Color::Black);

		sf::Vector2f fishermanPos = sf::Vector2f((_obj.globalSprt[GlobalS::FISHERMAN].getScale().x * _obj.globalTex[GlobalS::FISHERMAN].getSize().x) / 4.f + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().x,
			(_obj.globalSprt[GlobalS::FISHERMAN].getScale().y * _obj.globalTex[GlobalS::FISHERMAN].getSize().y) + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().y + 200.f);
		_obj.globalSprt[GlobalS::HOOK].setPosition(fishermanPos);

	}

	void animateFishing(float deltaTime) {
		elapsedFishing += deltaTime;
		if (elapsedFishing >= 0.5f) {
			frameFishing = (frameFishing + 1) % 4;

			float width = _obj.globalTex[GlobalS::FISHERMAN].getSize().x / 4.f;
			float height = _obj.globalTex[GlobalS::FISHERMAN].getSize().y;
			_obj.globalSprt[GlobalS::FISHERMAN].setTextureRect(sf::IntRect(frameFishing * static_cast<int>(width), 0, static_cast<int>(width), static_cast<int>(height)));

			elapsedFishing = 0.f;
		}
	}

	void animateFall(float deltaTime, Window_s& window) {
		static float elapsed = 0.0f;
		static int frame = 0;
		static bool transformed = false;
		static float angle = 0.0f;

		elapsed += deltaTime;

		// Animation de chute du pêcheur
		if (!transformed) {
			if (elapsed >= 0.5f && frame < 4) {
				float width = _obj.globalTex[GlobalS::FISHERMANS].getSize().x / 4.f;
				float height = _obj.globalTex[GlobalS::FISHERMANS].getSize().y;
				_obj.globalSprt[GlobalS::FISHERMANS].setTextureRect(sf::IntRect(frame * static_cast<int>(width), 0, static_cast<int>(width), static_cast<int>(height)));

				frame++;
				elapsed = 0.0f;
			}
			if (frame == 4) {
				transformed = true;
				_obj.globalSprt[GlobalS::FISHERMAN].setTexture(_obj.globalTex[GlobalS::FISHERMANF]);
				frame = 0;
			}
		}
		else {
			// Mouvement en arc de cercle dans l'eau
			sf::Vector2f center = sf::Vector2f(window.getWindow().getSize().x / 2.0f, window.getWindow().getSize().y / 2.0f);
			float radius = 200.0f; // Rayon de l'arc, ajustable
			float speed = 1.0f; // Vitesse de mouvement, ajustable

			angle += speed * deltaTime;
			if (angle > 2 * M_PI) {
				angle -= 2 * M_PI;
			}

			sf::Vector2f newPos = center + sf::Vector2f(radius * cos(angle), radius * sin(angle));
			_obj.globalSprt[GlobalS::FISHERMAN].setPosition(newPos);
		}
	}



	void animate(float deltaTime, Window_s& window) {
		// implement scene

		if (!isFishing) {
			animateFall(deltaTime, window);
			return;
		}


		animateFishing(deltaTime);
	}

	void updateLineToHook(sf::Sprite& hook) {
		sf::RectangleShape& line = _obj.globalRec[RectS::TRANS];

		sf::Vector2f fishermanPos = sf::Vector2f((_obj.globalSprt[GlobalS::FISHERMAN].getScale().x * _obj.globalTex[GlobalS::FISHERMAN].getSize().x) / 4.f + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().x, 
		(_obj.globalSprt[GlobalS::FISHERMAN].getScale().y * _obj.globalTex[GlobalS::FISHERMAN].getSize().y) + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().y);


		sf::Vector2f hookPos = hook.getPosition();

		line.setPosition(fishermanPos);

		sf::Vector2f direction = hookPos - fishermanPos;
		float distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

		line.setSize(sf::Vector2f(distance, 2.0f));

		float angle = atan2(direction.y, direction.x) * 180.0f / static_cast<float>(M_PI);
		line.setRotation(angle);
	}

	void handleEvent(const sf::Event& event, Window_s& window, Music& music) {

	}

	void counter() {
		sf::Vector2f viewSize = cameraView.getSize();
		sf::Vector2f viewCenter = cameraView.getCenter();
		sf::Vector2f fishCounterPos = sf::Vector2f(viewCenter.x + viewSize.x / 2 - (300 * 4), viewCenter.y - viewSize.y / 2 + (100 * 4));


	}

	void handleCollision(size_t fishIndex, Window_s &window) {
		returningToFisherman = true;
		fishCaught = true;
		caughtFishIndex = fishIndex;


		returnPosition = sf::Vector2f((_obj.globalSprt[GlobalS::FISHERMAN].getScale().x * _obj.globalTex[GlobalS::FISHERMAN].getSize().x) / 4.f + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().x,
			(_obj.globalSprt[GlobalS::FISHERMAN].getScale().y * _obj.globalTex[GlobalS::FISHERMAN].getSize().y) + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().y);
	}



	void trackDeletion(Window_s &window) {


		//count = window.countDeletionsInRange(static_cast<int>(Scene::SPRITESGB), static_cast<size_t>(GlobalS::FISHA), static_cast<size_t>(GlobalS::GEND));
		


	}


	void followHook(float deltaTime, Window_s& window) {
		sf::Sprite& hook = _obj.globalSprt[GlobalS::HOOK];


		if ((_obj.checkPixelCollision(hook, _obj.frontSprt[FrontS::MAPBORDER]) && !returningToFisherman) || (hook.getPosition().y < 0 && !returningToFisherman)){
			hook.setPosition(lastUpdatedHookPosition);
		}




		if (returningToFisherman) {
			sf::Vector2f currentPosition = hook.getPosition();
			sf::Vector2f direction = returnPosition - currentPosition;
			float speed = 2000.f;

			float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			if (length != 0) {
				direction.x /= length;
				direction.y /= length;
			}

			sf::Vector2f newPosition = currentPosition + speed * deltaTime * direction;
			hook.setPosition(newPosition);


			_obj.globalSprt[caughtFishIndex].setPosition(newPosition);



			if (length < 5.f) {
				returningToFisherman = false;
				sf::Vector2f hookPos = sf::Vector2f((_obj.globalSprt[GlobalS::FISHERMAN].getScale().x * _obj.globalTex[GlobalS::FISHERMAN].getSize().x) / 4.f + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().x,
					(_obj.globalSprt[GlobalS::FISHERMAN].getScale().y * _obj.globalTex[GlobalS::FISHERMAN].getSize().y) + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().y + 1000);

				window.removeFromRenderLayer(static_cast<int>(Scene::SPRITESGB), _obj.globalSprt[caughtFishIndex]);
				power.push_back(caughtFishIndex);
				count++;
				std::cout << count;
				if (count == 3)
					isFishing = false;

				
				hook.setPosition(hookPos);

			}
		}
		else {
			// Follow the mouse if not returning to the fisherman
			sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
			sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);

			sf::Vector2f currentPosition = hook.getPosition();
			sf::Vector2f direction = mousePosF - currentPosition;
			sf::Vector2f newPosition = currentPosition + 1.f * deltaTime * direction;
			hook.setPosition(newPosition);
		}
	}


	void update(float deltaTime, Window_s& window) {
		// implement scene
		if (!isFishing)
			return;

		timeSinceLastUpdate += deltaTime;
		if (timeSinceLastUpdate >= 0.5f) {
			lastUpdatedHookPosition = _obj.globalSprt[GlobalS::HOOK].getPosition();
			timeSinceLastUpdate = 0.0f;
		}

		for (size_t i = GlobalS::FISHA; i < GlobalS::GEND; i++) {
			if (_obj.globalSprt[GlobalS::HOOK].getGlobalBounds().intersects(_obj.globalSprt[i].getGlobalBounds())) {
				handleCollision(i, window);
				break;
			}
		}
		trackDeletion(window);
		followHook(deltaTime, window);
		updateLineToHook(_obj.globalSprt[GlobalS::HOOK]);
	}

	void updateCamera(float deltaTime, Window_s& window)
	{
		sf::Vector2f humanFishPosition = _obj.globalSprt[GlobalS::HOOK].getPosition();
		sf::Vector2f currentCameraCenter = cameraView.getCenter();
		float lat = 0.1f;
		sf::Vector2f newCameraCenter = currentCameraCenter + lat * (humanFishPosition - currentCameraCenter);

		cameraView.setCenter(newCameraCenter);
		cameraView.setSize(window.getWindow().getDefaultView().getSize() * 5.f);
		window.getWindow().setView(cameraView);
	}
};