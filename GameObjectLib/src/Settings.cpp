#include "Settings.hpp"

Settings::Settings() : _volume(100.0f), _fpsLimit(60), _resolution(1920, 1080)//, _menu() 
{
    _isMenu = true;
    _MenuState = SETTINGS;
    buttonCount = 0;
    _font.loadFromFile("asset/font/Beyonders.ttf");
}

void Settings::loadSettings(Window_s& window) {
	sf::Vector2f buttonSize(200, 50);
	std::vector<std::string> states = { "VOLUME", "RESOLTUION", "FPS LIMIT" };
	buttonCount = static_cast<unsigned int>(states.size());



	// Calcule de mise en page dynamique des boutons
	float spacing = 50;
	float centerX = window.getWindow().getSize().x / 2.0f;
	float firstButtonY = (window.getWindow().getSize().y - (buttonSize.y * buttonCount + spacing * (buttonCount - 1))) / 2.0f; // Dynamique set of buttons

	for (unsigned int i = 0; i < buttonCount; ++i) {
		sf::RectangleShape button(buttonSize);
		button.setFillColor(sf::Color(255, 0, 0)); // Set RGB color
		button.setOrigin(buttonSize.x / 2.0f, buttonSize.y / 2.0f);
		button.setPosition(centerX, firstButtonY + i * (buttonSize.y + spacing));
		mapButton[SETTINGS].push_back(button);
		buttonTexts.push_back(setTextOnButton(states[i], mapButton[SETTINGS][i]));
	}

}

void Settings::setVolume(float volume) {
    _volume = volume;
}

float Settings::getVolume() const {
    return _volume;
}

void Settings::setFpsLimit(unsigned int fps) {
    _fpsLimit = fps;
}

unsigned int Settings::getFpsLimit() const {
    return _fpsLimit;
}

void Settings::setResolution(const sf::Vector2u& resolution) {
    _resolution = resolution;
}

sf::Vector2u Settings::getResolution() const {
    return _resolution;
}
