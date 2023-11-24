#include "Settings.hpp"
#include <iostream>


Settings::Settings(Window_s& window, Music& music) :
_resolution(window.getWindow().getSize()), resolutionChanged(false), isVsync(false), vsyncChanged(false),
volumeSlider(200, 100, 200, 0, 100, music.getVolume()), // param : pos x, pos y, longueur, valeur min, valeur max, valeur actuelle
fpsSlider(200, 300, 200, 30, 244, window.getFps())
{
    buttonCount = 0;
    _fontButton.loadFromFile("asset/font/Beyonders.ttf");
	_fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
}

void Settings::load(Window_s& window) {
	// Slider creation for fps and volume
	sf::FloatRect boundfps = fpsSlider.getBar().getLocalBounds();
	sf::FloatRect boundvolume = volumeSlider.getBar().getLocalBounds();
	// Text for resolutions button
	sf::Text resolutionCaller = createText("Resolution :", sf::Vector2f(200, 400), 20);
	// Text for sliders
	sf::Text fpsCaller = createText("Frame rate :", sf::Vector2f(fpsSlider.getBar().getPosition().x , fpsSlider.getBar().getPosition().y - (boundfps.height * 5)), 20);
	sf::Text volumeCaller = createText("Volume rate :", sf::Vector2f(volumeSlider.getBar().getPosition().x, volumeSlider.getBar().getPosition().y - (boundvolume.height * 5)), 20);
	// Text for vsync
	sf::Text vsyncCaller = createText("Vsync :", sf::Vector2f(175, 525), 20);

	basicTexts.push_back(vsyncCaller);
	basicTexts.push_back(fpsCaller);
	basicTexts.push_back(volumeCaller);
	basicTexts.push_back(resolutionCaller);

	// Buttons for resolution
	sf::Vector2f buttonSize(180, 30);
	std::vector<std::string> states = { "Full screen", "1920 x 1080", "1600 x 900", "1536 x 864", "1440 x 900", "1366 x 768", "1280 x 720"};
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

	// Buttons for Vsync
	sf::Vector2f buttonSizeVsync(180, 75);
	sf::RectangleShape buttonVsync(buttonSizeVsync);

	buttonCount += 1;
	buttonVsync.setFillColor(sf::Color(255, 0, 0)); // Set RGB color
	buttonVsync.setOrigin(buttonSizeVsync.x / 2.0f, buttonSizeVsync.y / 2.0f);
	buttonVsync.setPosition(200, 600);
	mapButton.push_back(buttonVsync);
	if (isVsync)
		buttonTexts.push_back(setTextOnButton("On", buttonVsync, 25));
	else
		buttonTexts.push_back(setTextOnButton("Off", buttonVsync, 25));
}

void Settings::handleButtonClick(const sf::Event& event, Window_s& window, Music& music) {
	if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left) {
		return;
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
	sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);

	for (size_t i = 0; i < buttonTexts.size(); ++i) {
		if (mapButton[i].getGlobalBounds().contains(mousePosF)) {
			std::string buttonText = buttonTexts[i].getString(); // Get the text of the button
			sf::Vector2u oldResolution = _resolution;
			bool oldVsync = isVsync;

			if (buttonText == "Full screen") {
				_resolution = sf::Vector2u(0, 0);
			}
			else if (buttonText == "1920 x 1080") {
				_resolution = sf::Vector2u(1920, 1080);
			}
			else if (buttonText == "1600 x 900") {
				_resolution = sf::Vector2u(1600, 900);
			}
			else if (buttonText == "1536 x 864") {
				_resolution = sf::Vector2u(1536, 864);
			}
			else if (buttonText == "1440 x 900") {
				_resolution = sf::Vector2u(1440, 900);
			}
			else if (buttonText == "1366 x 768") {
				_resolution = sf::Vector2u(1366, 768);
			}
			else if (buttonText == "1280 x 720") {
				_resolution = sf::Vector2u(1280, 720);
			}
			else if (buttonText == "On") {
				isVsync = false;
			}
			else if (buttonText == "Off") {
				isVsync = true;
			}

			if (oldVsync != isVsync) {
				vsyncChanged = true;
			}
			if (oldResolution != _resolution) {
				resolutionChanged = true;
			}
			break;
		}
		std::cout << isVsync;
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
	// Fps 
	if (fpsSlider.getisDragging()) {
		window.setFps(static_cast<unsigned int>(fpsSlider.getValue()));
	}
	// Volume
	if (volumeSlider.getisDragging()) {
		music.setVolume(volumeSlider.getValue());
	}

	// Resolution
	if (resolutionChanged) {
		sf::RenderWindow& rw = window.getWindow();
		if (_resolution == sf::Vector2u(0, 0)) {
			rw.create(sf::VideoMode::getDesktopMode(), window.getTitle(), sf::Style::Fullscreen);
		}
		else {
			rw.create(sf::VideoMode(_resolution.x, _resolution.y), window.getTitle(), sf::Style::Default);
		}
		rw.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - rw.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - rw.getSize().y / 2));
		resolutionChanged = false;
	}

	// Vsync
	if (vsyncChanged) {
		std::string Off = "Off";
		std::string On = "On";
		for (int i = 0; i < buttonTexts.size(); ++i) {
			if (buttonTexts[i].getString() == Off) {
				buttonTexts[i].setString(On);
				break;
			}
			if (buttonTexts[i].getString() == On) {
				buttonTexts[i].setString(Off);
				break;
			}
		}
		window.getWindow().setVerticalSyncEnabled(isVsync);
		vsyncChanged = false;
	}
}