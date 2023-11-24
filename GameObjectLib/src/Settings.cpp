#include "Settings.hpp"
#include <iostream>


Settings::Settings(Window_s& window, Music& music) : 
volumeSlider(200, 100, 200, 0, 100, music.getVolume()), // param : pos x, pos y, longueur, valeur min, valeur max, valeur actuelle
fpsSlider(200, 300, 200, 30, 244, window.getFps())
{
    _MenuState = SETTINGS;
    buttonCount = 0;
    _fontButton.loadFromFile("asset/font/Beyonders.ttf");
	_fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
}

void Settings::loadSettings(Window_s& window) {
	// Slider creation for fps and volume
	sf::FloatRect boundfps = fpsSlider.getBar().getLocalBounds();
	sf::FloatRect boundvolume = volumeSlider.getBar().getLocalBounds();
	// Text for resolutions button
	sf::Text resolutionCaller = createText("Resolution :", sf::Vector2f(200, 450 - (boundvolume.height * 5)), 20);
	// Text for sliders
	sf::Text fpsCaller = createText("Frame rate :", sf::Vector2f(fpsSlider.getBar().getPosition().x , fpsSlider.getBar().getPosition().y - (boundfps.height * 5)), 20);
	sf::Text volumeCaller = createText("Volume rate :", sf::Vector2f(volumeSlider.getBar().getPosition().x, volumeSlider.getBar().getPosition().y - (boundvolume.height * 5)), 20);

	basicTexts.push_back(fpsCaller);
	basicTexts.push_back(volumeCaller);
	basicTexts.push_back(resolutionCaller);

	// Buttons for resolution
	sf::Vector2f buttonSize(180, 30);
	std::vector<std::string> states = { "Full screen", "1920 x 1080", "1600 x 900", "1536 x 864", "1440 x 900", "1366 x 768", "1280 x 720" };
	buttonCount = static_cast<unsigned int>(states.size());

	float spacing = 175;

	for (unsigned int i = 0; i < buttonCount; ++i) {
		sf::RectangleShape button(buttonSize);
		button.setFillColor(sf::Color(255, 0, 0)); // Set RGB color
		button.setOrigin(buttonSize.x / 2.0f, buttonSize.y / 2.0f);
		button.setPosition(200 + i * (buttonSize.y + spacing), 450);
		mapButton.push_back(button);
		buttonTexts.push_back(setTextOnButton(states[i], mapButton[i], 15));
	}
}

void Settings::drawSliders(Window_s& window) {
    volumeSlider.draw(window);
    fpsSlider.draw(window);
}



void Settings::handleMouseDrag(const sf::Event& event, Window_s& window) {
    volumeSlider.handleMouseDrag(event, window.getWindow());
    fpsSlider.handleMouseDrag(event, window.getWindow());
}

void Settings::valueChanger(Window_s& window, Music& music) {
	window.setFps(fpsSlider.getValue());
	music.setVolume(volumeSlider.getValue());

}