#include "FisherMan.hpp"

FicherMan::FicherMan(PlayObject& obj, sf::View& _cameraView) : _obj(obj), cameraView(_cameraView), gen(rd()) {
	timeSinceLastUpdate = 0.0f;
	isFishing = true;
	isDefFishing = true;
	returningToFisherman = false;
	fishCaught = false;
	caughtFishIndex = 0;
	frameFishing = 0;
	elapsedFishing = 0.f;
	count = 0;
	elapsedFall = 0.7f;
	frameFall = 0;
	callOnce = false;
	elapsedSwitch = 0.f;
	elapsedTotal = 0.f;

	elapsedStart = 0.f;
}

void FicherMan::resetValues() {
	timeSinceLastUpdate = 0.0f;
	isFishing = true;
	isDefFishing = true;
	returningToFisherman = false;
	fishCaught = false;
	caughtFishIndex = 0;
	frameFishing = 0;
	elapsedFishing = 0.f;
	count = 0;
	elapsedFall = 0.7f;
	frameFall = 0;
	callOnce = false;
	elapsedSwitch = 0.f;
	elapsedTotal = 0.f;

	elapsedStart = 0.f;

}

const bool FicherMan::getIsDefFishing() const {
	return isDefFishing;
}

const std::vector<int> FicherMan::getPowers() const {
	return power;
}

void FicherMan::load(Window_s& window) {
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



void FicherMan::animateFishing(float deltaTime) {
	elapsedFishing += deltaTime;
	if (elapsedFishing >= 0.5f) {
		frameFishing = (frameFishing + 1) % 4;

		float width = static_cast<float>(_obj.globalTex[GlobalS::FISHERMAN].getSize().x) / 4.f;
		float height = static_cast<float>(_obj.globalTex[GlobalS::FISHERMAN].getSize().y);
		_obj.globalSprt[GlobalS::FISHERMAN].setTextureRect(sf::IntRect(frameFishing * static_cast<int>(width), 0, static_cast<int>(width), static_cast<int>(height)));

		elapsedFishing = 0.f;
	}
}

void FicherMan::animateFall(float deltaTime, Window_s& window) {
	elapsedFall += deltaTime;


	// cam control
	sf::Vector2f humanFishPosition = _obj.globalSprt[GlobalS::FISHERMANS].getPosition();
	sf::Vector2f currentCameraCenter = cameraView.getCenter();
	sf::Vector2f newCameraCenter = currentCameraCenter + 0.1f * (humanFishPosition - currentCameraCenter);
	newCameraCenter.y += 30.f;
	cameraView.setCenter(newCameraCenter);
	cameraView.setSize(window.getWindow().getDefaultView().getSize() * 3.f);
	window.getWindow().setView(cameraView);

	if (_obj.globalSprt[GlobalS::HOOK].getPosition().y < 10000.f)
		_obj.globalSprt[GlobalS::HOOK].move(sf::Vector2f(0, _obj.globalSprt[GlobalS::HOOK].getPosition().y * deltaTime));

	if (elapsedFall >= 0.7f && frameFall != 4) {
		frameFall = (frameFall + 1) % 5;

		float width = static_cast<float>(_obj.globalTex[GlobalS::FISHERMANS].getSize().x) / 5.f;
		float height = static_cast<float>(_obj.globalTex[GlobalS::FISHERMANS].getSize().y);
		_obj.globalSprt[GlobalS::FISHERMANS].setTextureRect(sf::IntRect(frameFall * static_cast<int>(width), 0, static_cast<int>(width), static_cast<int>(height)));


		if (frameFall == 1) {
			_obj.globalRec[RectS::FLASH].setFillColor(sf::Color(255, 255, 255, 180)); // Flash semi-transparent
		}
		else {
			_obj.globalRec[RectS::FLASH].setFillColor(sf::Color::Transparent);
		}

		elapsedFall = 0.f;
	}





	// condition to stop the falling
	if (_obj.globalSprt[GlobalS::FISHERMANS].getPosition().y >= -300.f) {

		elapsedSwitch += deltaTime;

		if (!callOnce) {




			// add flash for 2 seconde
			_obj.globalSprt[GlobalS::FISHERMANS].setTexture(_obj.globalTex[GlobalS::FISHERMANF], true);
			_obj.globalSprt[GlobalS::FISHERMANS].setPosition(sf::Vector2f(_obj.globalSprt[GlobalS::FISHERMANS].getPosition().x, 300));
			_obj.globalSprt[GlobalS::FISHERMANS].setScale(5.f, 5.f);
			_obj.globalSprt[GlobalS::FISHERMANS].setOrigin(FRAME_WIDTH / 2.f, FRAME_HEIGHT / 2.f);
			_obj.globalSprt[GlobalS::FISHERMANS].setTextureRect(sf::IntRect(static_cast<int>(FRAME_WIDTH), 0, static_cast<int>(FRAME_WIDTH), static_cast<int>(FRAME_HEIGHT)));
			callOnce = true;
		}


		if (elapsedSwitch >= 3.0f) {
			isDefFishing = false;
		}
		// after 5 seconde in this function add flash

	}
	else {
		_obj.globalSprt[GlobalS::FISHERMANS].move(sf::Vector2f(0, 0.2f * std::abs(_obj.globalSprt[GlobalS::FISHERMANS].getPosition().y) * deltaTime));
	}


}



void FicherMan::animate(float deltaTime, Window_s& window) {
	// implement scene

	if (!isFishing) {
		animateFall(deltaTime, window);
		return;
	}


	animateFishing(deltaTime);
}

void FicherMan::updateLineToHook(sf::Sprite& hook) {
	sf::RectangleShape& line = _obj.globalRec[RectS::TRANS];

	sf::Vector2f fishermanPos = sf::Vector2f((_obj.globalSprt[GlobalS::FISHERMAN].getScale().x * _obj.globalTex[GlobalS::FISHERMAN].getSize().x) / 4.f + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().x,
		(_obj.globalSprt[GlobalS::FISHERMAN].getScale().y * _obj.globalTex[GlobalS::FISHERMAN].getSize().y) + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().y);


	sf::Vector2f hookPos = hook.getPosition();

	line.setPosition(fishermanPos);

	sf::Vector2f direction = hookPos - fishermanPos;
	float distance = static_cast<float>(sqrt(pow(direction.x, 2.f) + pow(direction.y, 2.f)));

	line.setSize(sf::Vector2f(distance, 2.0f));

	float angle = atan2(direction.y, direction.x) * 180.0f / static_cast<float>(M_PI);
	line.setRotation(angle);
}

void FicherMan::handleEvent(const sf::Event& event, Window_s& window, Music& music) {

}


void FicherMan::handleCollision(size_t fishIndex, Window_s& window) {
	returningToFisherman = true;
	fishCaught = true;
	caughtFishIndex = static_cast<int>(fishIndex);


	returnPosition = sf::Vector2f((_obj.globalSprt[GlobalS::FISHERMAN].getScale().x * _obj.globalTex[GlobalS::FISHERMAN].getSize().x) / 4.f + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().x,
		(_obj.globalSprt[GlobalS::FISHERMAN].getScale().y * _obj.globalTex[GlobalS::FISHERMAN].getSize().y) + _obj.globalSprt[GlobalS::FISHERMAN].getPosition().y);
}


void FicherMan::followHook(float deltaTime, Window_s& window) {
	sf::Sprite& hook = _obj.globalSprt[GlobalS::HOOK];


	if ((_obj.checkPixelCollision(hook, _obj.frontSprt[FrontS::MAPBORDER]) && !returningToFisherman) || (hook.getPosition().y < 0 && !returningToFisherman)) {
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
			if (count == 3) {
				// change to animation
				isFishing = false;
				_obj.globalSprt[GlobalS::FISHERMANS].setTexture(_obj.globalTex[GlobalS::FISHERMANS]);
				_obj.globalSprt[GlobalS::FISHERMANS].setScale(sf::Vector2f((_obj.globalSprt[GlobalS::FISHERMAN].getScale().x * _obj.globalTex[GlobalS::FISHERMAN].getSize().x) / _obj.globalTex[GlobalS::FISHERMANS].getSize().x,
					(_obj.globalSprt[GlobalS::FISHERMAN].getScale().y * _obj.globalTex[GlobalS::FISHERMAN].getSize().y) / _obj.globalTex[GlobalS::FISHERMANS].getSize().y));
				_obj.globalSprt[GlobalS::FISHERMANS].setPosition(_obj.globalSprt[GlobalS::FISHERMAN].getPosition());
				window.removeFromRenderLayer(static_cast<int>(Scene::SPRITESGB), _obj.globalSprt[GlobalS::FISHERMAN]);

			}


			hook.setPosition(hookPos);

		}
	}
	else if (elapsedStart >= 5.f) {
		// Follow the mouse if not returning to the fisherman
		sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
		sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);

		sf::Vector2f currentPosition = hook.getPosition();
		sf::Vector2f direction = mousePosF - currentPosition;
		sf::Vector2f newPosition = currentPosition + 1.f * deltaTime * direction;
		hook.setPosition(newPosition);

	}
	elapsedStart += deltaTime;
}


void FicherMan::update(float deltaTime, Window_s& window) {




	// implement scene
	if (!isFishing)
		return;

	elapsedTotal += deltaTime;


	if (elapsedTotal > 100.f) {
		fillVectorWithRandom(power, GlobalS::FISHA, GlobalS::GEND);
		for (const auto& pow : power) {
			std::cout << pow << std::endl;
		}
		isFishing = false;
		isDefFishing = false;
	}

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

	followHook(deltaTime, window);
	updateLineToHook(_obj.globalSprt[GlobalS::HOOK]);
}

void FicherMan::fillVectorWithRandom(std::vector<int>& vec, int minVal, int maxVal) {

	std::uniform_int_distribution<> distrib(minVal, maxVal - 1); // Distribution entre minVal et maxVal (exclus)

	// Calcule combien d'�l�ments � ajouter (jusqu'� un maximum de 3)
	int elementsToAdd = std::min(3 - static_cast<int>(vec.size()), 3);

	for (int i = 0; i < elementsToAdd; ++i) {
		vec.push_back(distrib(gen)); // Ajoute un �l�ment al�atoire
	}
}

void FicherMan::updateCamera(float deltaTime, Window_s& window)
{
	if (!isFishing)
		return;

	sf::Vector2f humanFishPosition = _obj.globalSprt[GlobalS::HOOK].getPosition();
	sf::Vector2f currentCameraCenter = cameraView.getCenter();
	float lat = 0.1f;
	sf::Vector2f newCameraCenter = currentCameraCenter + lat * (humanFishPosition - currentCameraCenter);

	cameraView.setCenter(newCameraCenter);
	cameraView.setSize(window.getWindow().getDefaultView().getSize() * 3.f);
	window.getWindow().setView(cameraView);
}