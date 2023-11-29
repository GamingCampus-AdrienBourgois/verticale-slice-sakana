#include "Settings.hpp"

Settings::Settings(Window_s& window, Music& music) : 
	_resolution(window.getWindow().getSize()),
	resolutionChanged(false),
	Vsync(false),
	vsyncChanged(false),
	pauseChanged(false),
	isMax(false),
	isMin(false),
	paused(false),
	settingsFile("Save/saveSettings.txt")
{
	// Appliquer tous les paramatres modifiés
	valueSetter(window, music);

	// Initialisez maintenant les sliders avec les valeurs maj
	volumeSlider = std::make_unique<Slider>(200, 100, 200, 0, 100, music.getVolume());
	fpsSlider = std::make_unique<Slider>(200, 300, 200, 30, 244, window.getFps());


	_fontButton.loadFromFile("asset/font/Beyonders.ttf");
	_fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
}

void Settings::textureSetters(Window_s& window) {
	sf::Vector2u windowSize = window.getWindow().getSize();
	float X = static_cast<float>(windowSize.x);
	float Y = static_cast<float>(windowSize.y);

	// load texture and create de sprite 
	std::vector<std::string> globaleFile = { "asset/sprite/settings/background.png" };

	bgTex.resize(globaleFile.size());
	bgSprt.resize(globaleFile.size());

	for (size_t i = 0; i < globaleFile.size(); i++) {
		if (!bgTex[i].loadFromFile(globaleFile[i])) {
			throw std::runtime_error("Failed to load texture");
		}
		else {
			bgSprt[i].setTexture(bgTex[i]);
		}
	}
	// here we set scale/position/origin
	bgSprt[0].setScale(X / bgTex[0].getSize().x, Y / bgTex[0].getSize().y); // attapt pos to screen size

	// load texture on buttons
	buttonTex.resize(buttons.size());

	for (size_t i = 0; i < buttons.size(); i++) {
		if (!buttonTex[i].loadFromFile("asset/sprite/menu/woodButton.jpg")) {
			throw std::runtime_error("Failed to load texture");
		}
		else {
			buttons[i].setTexture(&buttonTex[i]);
		}
	}
}

void Settings::load(Window_s& window) {
	// Slider creation for fps and volume
	sf::FloatRect boundfps = fpsSlider->getBar().getLocalBounds();
	sf::FloatRect boundvolume = volumeSlider->getBar().getLocalBounds();


	// Text for declaration
	// Text for resolutions button
	sf::Text resolutionCaller = createText("Resolution :", sf::Vector2f(100, 375), 20, sf::Color(255, 255, 255));
	// Text for sliders
	sf::Text fpsCaller = createText("Frame rate :", sf::Vector2f(100 , fpsSlider->getBar().getPosition().y - (boundfps.height * 5)), 20, sf::Color(255, 255, 255));
	sf::Text volumeCaller = createText("Volume rate :", sf::Vector2f(100, volumeSlider->getBar().getPosition().y - (boundvolume.height * 5)), 20, sf::Color(255, 255, 255));
	// Text for vsync
	sf::Text vsyncCaller = createText("Vsync :", sf::Vector2f(100, 525), 20, sf::Color(255, 255, 255));
	globalTexts.push_back(vsyncCaller);
	globalTexts.push_back(fpsCaller);
	globalTexts.push_back(volumeCaller);
	globalTexts.push_back(resolutionCaller);


	// BackGround for text
	std::vector<sf::Text*> texts = { &resolutionCaller, &fpsCaller, &volumeCaller, &vsyncCaller };
	for (auto text : texts) {
		sf::FloatRect textRect = text->getLocalBounds();
		sf::RectangleShape background(sf::Vector2f(textRect.width + 10, textRect.height + 10));
		background.setFillColor(sf::Color(255, 0, 0));
		background.setOutlineThickness(2);
		background.setOrigin(background.getSize().x / 2, background.getSize().y / 2);
		background.setPosition(text->getPosition().x, text->getPosition().y);
		particles.push_back(background);
	}


	// Buttons for resolution
	sf::Vector2f buttonSize(180, 30);
	std::vector<std::string> states = { "Full screen", "1920 x 1080", "1600 x 900", "1536 x 864", "1440 x 900", "1366 x 768", "1280 x 720"};
	float spacing = 175;

	for (size_t i = 0; i < states.size(); ++i) {
		sf::RectangleShape button(buttonSize);
		button.setFillColor(sf::Color(255, 0, 0)); // Set RGB color
		button.setOrigin(buttonSize.x / 2.0f, buttonSize.y / 2.0f);
		button.setPosition(200 + i * (buttonSize.y + spacing), 450);
		button.setOutlineThickness(1);
		buttons.push_back(button);
		buttonTexts.push_back(setTextOnButton(states[i], buttons[i], 15, sf::Color(0, 255, 0)));
	}

	
	// Buttons for volume max and min
	sf::Vector2f buttonSizeVolume(120, 30);
	std::vector<std::string> volumeStates = { "Mute", "Max" };
	if (paused)
		volumeStates.push_back("Play");
	else
		volumeStates.push_back("Pause");

	float spacingVolume = 100;

	for (size_t i = 0; i < volumeStates.size(); i++) {
		sf::RectangleShape buttonVolume(buttonSizeVolume);
		buttonVolume.setFillColor(sf::Color(255, 0, 0)); // Set RGB color
		buttonVolume.setOrigin(buttonSizeVolume.x / 2.0f, buttonSizeVolume.y / 2.0f);
		buttonVolume.setPosition(150 + i * (buttonSizeVolume.y + spacingVolume), 175);
		buttonVolume.setOutlineThickness(1);
		buttons.push_back(buttonVolume);
		buttonTexts.push_back(setTextOnButton(volumeStates[i], buttons[i + states.size()], 15, sf::Color(0, 255, 0)));
	}


	// Buttons for Vsync
	sf::Vector2f buttonSizeVsync(180, 75);
	sf::RectangleShape buttonVsync(buttonSizeVsync);

	buttonVsync.setFillColor(sf::Color(255, 0, 0)); // Set RGB color
	buttonVsync.setOrigin(buttonSizeVsync.x / 2.0f, buttonSizeVsync.y / 2.0f);
	buttonVsync.setPosition(200, 625);
	buttonVsync.setOutlineThickness(1);
	buttons.push_back(buttonVsync);
	if (Vsync)
		buttonTexts.push_back(setTextOnButton("On", buttonVsync, 25, sf::Color(0, 255, 0)));
	else
		buttonTexts.push_back(setTextOnButton("Off", buttonVsync, 25, sf::Color(0, 255, 0)));


	// Texture for sprite or buttons
	textureSetters(window);
}

void Settings::handleButtonClick(const sf::Event& event, Window_s& window, Music& music) {
	if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left) {
		return;
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
	sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);

	for (size_t i = 0; i < buttonTexts.size(); ++i) {
		if (buttons[i].getGlobalBounds().contains(mousePosF)) {
			std::string buttonText = buttonTexts[i].getString(); // Get the text of the button
			sf::Vector2u oldResolution = _resolution;
			bool oldVsync = Vsync;
			bool oldPause = paused;

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
				Vsync = false;
			}
			else if (buttonText == "Off") {
				Vsync = true;
			}
			else if (buttonText == "Mute") {
				isMin = true;
			}
			else if (buttonText == "Max") {
				isMax = true;
			}
			else if (buttonText == "Pause") {
				paused = true;
			}
			else if (buttonText == "Play") {
				paused = false;
			}

			if (oldPause != paused) {
				pauseChanged = true;
			}

			if (oldVsync != Vsync) {
				vsyncChanged = true;
			}
			if (oldResolution != _resolution) {
				resolutionChanged = true;
			}
			break;
		}
	}
}

void Settings::drawSliders(Window_s& window) {
    volumeSlider->draw(window);
    fpsSlider->draw(window);
}

void Settings::handleMouseDrag(const sf::Event& event, Window_s& window) {
    volumeSlider->handleMouseDrag(event, window.getWindow());
    fpsSlider->handleMouseDrag(event, window.getWindow());
}

void Settings::valueChanger(Window_s& window, Music& music) {

	// Fps
	if (fpsSlider->getisDragging()) {
		unsigned int fpsValue = static_cast<unsigned int>(fpsSlider->getValue());
		window.setFps(fpsValue);
		GameStatistics::saveSettingsValue("FramePerSecond", settingsFile, std::to_string(fpsValue));
	}

	// Volume
	if (volumeSlider->getisDragging()) {
		float volumeValue = volumeSlider->getValue();
		music.setVolume(volumeValue);
		GameStatistics::saveSettingsValue("Volume", settingsFile, std::to_string(volumeValue));
	}
	if (isMax) { // buttons volume
		float volumeMax = 100;
		volumeSlider->setValue(volumeMax);
		music.setVolume(volumeMax);
		GameStatistics::saveSettingsValue("Volume", settingsFile, std::to_string(volumeMax));
		isMax = false;
	}
	if (isMin) { // buttons volume
		float volumeMin = 0;
		volumeSlider->setValue(volumeMin);
		music.setVolume(volumeMin);
		GameStatistics::saveSettingsValue("Volume", settingsFile, std::to_string(volumeMin));
		isMin = false;
	}
	if (pauseChanged) { // buttons volume
		std::string pauseValue = paused ? "Play" : "Pause";
		for (int i = 0; i < buttonTexts.size(); ++i) {
			if (buttonTexts[i].getString() == "Pause" || buttonTexts[i].getString() == "Play") {
				buttonTexts[i].setString(pauseValue);
				
				break;
			}
		}
		if (!paused) {
			music.setPause(paused);
			music.playMusic(MSETTINGS);

		}
		else {
			music.setPause(paused);
			music.pauseMusic();
		}
		pauseChanged = false;
	}

	// Resolution
	if (resolutionChanged) {
		sf::RenderWindow& rw = window.getWindow();
		std::string resolutionValue;
		if (_resolution == sf::Vector2u(0, 0)) {
			rw.create(sf::VideoMode::getDesktopMode(), window.getTitle(), sf::Style::Fullscreen);
			resolutionValue = "0x0"; // Full screen
		}
		else {
			rw.create(sf::VideoMode(_resolution.x, _resolution.y), window.getTitle(), sf::Style::Default);
			resolutionValue = std::to_string(_resolution.x) + "x" + std::to_string(_resolution.y);
		}
		rw.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - rw.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - rw.getSize().y / 2));
		GameStatistics::saveSettingsValue("Resolution", settingsFile, resolutionValue);
		sf::Vector2u windowSize = window.getWindow().getSize();
		float X = static_cast<float>(windowSize.x);
		float Y = static_cast<float>(windowSize.y);
		bgSprt[0].setScale(X / bgTex[0].getSize().x, Y / bgTex[0].getSize().y);
		resolutionChanged = false;
	}

	// Vsync
	if (vsyncChanged) {
		std::string vsyncValue = Vsync ? "On" : "Off";
		for (int i = 0; i < buttonTexts.size(); ++i) {
			if (buttonTexts[i].getString() == "Off" || buttonTexts[i].getString() == "On") {
				buttonTexts[i].setString(vsyncValue);
				break;
			}
		}
		window.getWindow().setVerticalSyncEnabled(Vsync);
		GameStatistics::saveSettingsValue("Vsync", settingsFile, vsyncValue);
		vsyncChanged = false;
	}
}

void Settings::valueSetter(Window_s& window, Music& music) {
	std::string fpsStr = GameStatistics::getParamFromString("FramePerSecond", settingsFile);
	std::string volumeStr = GameStatistics::getParamFromString("Volume", settingsFile);
	std::string resolutionStr = GameStatistics::getParamFromString("Resolution", settingsFile);
	std::string vsyncStr = GameStatistics::getParamFromString("Vsync", settingsFile);

	try {
		// FPS 
		if (!fpsStr.empty()) {
			unsigned int fps = static_cast<unsigned int>(std::stoi(fpsStr));
			window.setFps(fps);
		}
		// VOLUME
		if (!volumeStr.empty()) {
			float volume = std::stof(volumeStr);
			music.setVolume(volume);
		}

		// RESOLUTION
		if (!resolutionStr.empty()) {
			size_t xIndex = resolutionStr.find('x');
			if (xIndex != std::string::npos) {
				unsigned int width = std::stoi(resolutionStr.substr(0, xIndex));
				unsigned int height = std::stoi(resolutionStr.substr(xIndex + 1));
				_resolution = sf::Vector2u(width, height);
				// set the screen res
				sf::RenderWindow& rw = window.getWindow();
				if (_resolution == sf::Vector2u(0, 0)) {
					rw.create(sf::VideoMode::getDesktopMode(), window.getTitle(), sf::Style::Fullscreen);
				}
				else {
					rw.create(sf::VideoMode(_resolution.x, _resolution.y), window.getTitle(), sf::Style::Default);
				}
				rw.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2 - rw.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - rw.getSize().y / 2));
			}
		}
		// VSYNC
		if (!vsyncStr.empty()) {
			Vsync = (vsyncStr == "On"); // ez way to attribute a bool
			window.getWindow().setVerticalSyncEnabled(Vsync);
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Erreur lors de la conversion des param�tres: " << e.what() << std::endl;
	}
}

const std::string Settings::getSettingsFile() const {
	return settingsFile;
}

void Settings::reloding(Window_s &window) {
	resetValues(window);
	load(window);
	// add Sliders
	drawSliders(window);
	draw(window);
}