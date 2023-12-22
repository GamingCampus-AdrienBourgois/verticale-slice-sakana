#pragma once
#include <SFML/Graphics.hpp>
#include "GameStatistics.hpp"
#include "PlayObject.hpp"
#include <vector>
#include <random>

class FicherMan {
public:
	FicherMan(PlayObject& obj, sf::View& _cameraView);
	~FicherMan() = default;
	void resetValues();
	const bool getIsDefFishing() const;
	const std::vector<int> getPowers() const;
	void load(Window_s& window);
	void animate(float deltaTime, Window_s& window);
	void updateLineToHook(sf::Sprite& hook);
	void handleEvent(const sf::Event& event, Window_s& window, Music& music);
	void handleCollision(size_t fishIndex, Window_s& window);
	void followHook(float deltaTime, Window_s& window);
	void update(float deltaTime, Window_s& window);
	void fillVectorWithRandom(std::vector<int>& vec, int minVal, int maxVal);
	void updateCamera(float deltaTime, Window_s& window);

	void animateFishing(float deltaTime);
	void animateFall(float deltaTime, Window_s& window);
private:
	PlayObject& _obj;

	sf::View& cameraView;

	std::vector<int> power;


	// anim
	float elapsedFishing;
	int frameFishing;
	int count;

	float elapsedFall;
	int frameFall;
	bool callOnce;


	float elapsedSwitch;

	float elapsedTotal;

	bool returningToFisherman;
	sf::Vector2f returnPosition;
	bool fishCaught;
	int caughtFishIndex;

	sf::Vector2f lastUpdatedHookPosition;
	float timeSinceLastUpdate;

	bool isFishing;
	bool isDefFishing;

	float elapsedStart;

	std::random_device rd; // G�n�rateur de nombres al�atoires
	std::mt19937 gen;

	static constexpr float FRAME_WIDTH = 29.f;
	static constexpr float FRAME_HEIGHT = 21.f;
	static constexpr float M_PI = 3.1416f;
};
