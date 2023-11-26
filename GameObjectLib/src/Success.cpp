#include "Success.hpp"

Success::Success() : file("Save/saveStatistics.txt"), clickS(false), openS(false), timeS(false), elapsed(0)
{
	buttonCount = 0;
	_fontButton.loadFromFile("asset/font/Beyonders.ttf");
	_fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
}

void Success::textureSetters(Window_s& window) {
	sf::Vector2u windowSize = window.getWindow().getSize(); // attapt to creen size
	float X = static_cast<float>(windowSize.x);
	float Y = static_cast<float>(windowSize.y);

	// load texture and create de sprite 
	std::vector<std::string> backgroundFile = { "asset/sprite/success/background.png" };
	std::vector<std::string> globalFile = { "asset/sprite/success/Cadenas.png", "asset/sprite/success/Cadenas.png", "asset/sprite/success/Cadenas.png",  "asset/sprite/success/Hourglass.png",  "asset/sprite/success/Open.png",  "asset/sprite/success/Click.png" };



	bgTex.resize(backgroundFile.size());
	bgSprt.resize(backgroundFile.size());

	globalTex.resize(globalFile.size());
	globalSprt.resize(globalFile.size());

	if (!bgTex[0].loadFromFile(backgroundFile[0])) {
		throw std::runtime_error("Failed to load texture");
	} else {
		bgSprt[0].setTexture(bgTex[0]);
	}

	for (size_t i = 0; i < globalFile.size(); i++) {
		if (!globalTex[i].loadFromFile(globalFile[i])) {
			throw std::runtime_error("Failed to load texture");
		}
		else {
			globalSprt[i].setTexture(globalTex[i]);
		}
	}
	// here we set scale/position/origin
	bgSprt[0].setScale(X / bgTex[0].getSize().x, Y / bgTex[0].getSize().y); // attapt scale to screen size

	
	for (size_t i = 0; i < globalSprt.size(); i++) {
		globalSprt[i].setScale(particles[0].getSize().x / globalTex[i].getSize().x, particles[0].getSize().y / globalTex[i].getSize().y);
		globalSprt[i].setOrigin(sf::Vector2f(globalTex[i].getSize().x / 2, globalTex[i].getSize().y / 2));

		globalSprt[i].setPosition(sf::Vector2f(particles[i].getPosition().x, particles[i].getPosition().y));
	}
	for (size_t i = globalFile.size() / 2; i < globalFile.size(); i++)
	{
		globalSprt[i].setPosition(sf::Vector2f(-200, globalSprt[i].getPosition().y));
	}
}

void Success::load(Window_s& window) {
	sf::Text successTime = createText(GameStatistics::getParamFromString("timePlaying", file) + " Hours", sf::Vector2f(300, 100), 20, sf::Color(255, 255, 255));
	sf::Text successOppened = createText(GameStatistics::getParamFromString("gameOpenned", file) + " Oppened", sf::Vector2f(300, 300), 20, sf::Color(255, 255, 255));
	sf::Text successClick = createText(GameStatistics::getParamFromString("clicks", file) + " Click", sf::Vector2f(300, 500), 20, sf::Color(255, 255, 255));

	basicTexts.push_back(successTime);
	basicTexts.push_back(successOppened);
	basicTexts.push_back(successClick);

	// Cadre for success
	sf::Vector2f buttonSize(150, 150);
	float spacing = 200;

	for (int i = 0; i < 2; i++) {
		for (size_t i = 0; i < basicTexts.size(); ++i) {
			sf::RectangleShape button(buttonSize);
			button.setFillColor(sf::Color(208, 243, 112)); // Set RGB color
			button.setOrigin(buttonSize.x / 2.0f, buttonSize.y / 2.0f);
			button.setPosition(100, 100 + (i * spacing));
			button.setOutlineThickness(5);
			button.setOutlineColor(sf::Color(0, 0, 0));
			particles.push_back(button);
		}
	}

	textureSetters(window);
}

void Success::update(float deltaTime) {
	elapsed += deltaTime;


	if (elapsed > 4.0f) {
		std::string timeStr = GameStatistics::getParamFromString("timePlaying", file);
		size_t dotPos = timeStr.find('.');
		int minutes = std::stoi(timeStr.substr(0, dotPos));
		int seconds = std::stoi(timeStr.substr(dotPos + 1));
		float totalTime = minutes * 60 + seconds;

		if (totalTime > 60) { // 10 minutes 
			globalSprt[3].setPosition(sf::Vector2f(particles[3].getPosition().x, particles[3].getPosition().y));
			globalSprt[0].setPosition(sf::Vector2f(-200, globalSprt[0].getPosition().y));

		}

		std::string openStr = GameStatistics::getParamFromString("gameOpenned", file);
		int openInt = std::stoi(openStr);
		if (openInt > 100) {
			globalSprt[4].setPosition(sf::Vector2f(particles[4].getPosition().x, particles[4].getPosition().y));
			globalSprt[1].setPosition(sf::Vector2f(-200, globalSprt[1].getPosition().y));
		}


		std::string clickStr = GameStatistics::getParamFromString("clicks", file);
		int clickInt = std::stoi(clickStr);
		if (clickInt > 100) {
			globalSprt[5].setPosition(sf::Vector2f(particles[5].getPosition().x, particles[5].getPosition().y));
			globalSprt[2].setPosition(sf::Vector2f(-200, globalSprt[2].getPosition().y));
		}
	}

}