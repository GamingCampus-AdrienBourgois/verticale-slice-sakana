#include "Menu.hpp"

Menu::Menu(Window_s& window, Music& music) : _settings(window, music)
{
	_isMenu = true;
	_MenuState = BASE;
	buttonCount = 0;
	_fontButton.loadFromFile("asset/font/Beyonders.ttf");


}

Menu::~Menu() = default;


void Menu::loadMenuButton(Window_s& window)
{
	sf::Vector2f buttonSize(200, 50);
	std::vector<std::string> states = { "PLAY", "SETTINGS", "HELP", "SUCCESS", "CREDIT", "QUIT" };
	buttonCount = static_cast<unsigned int>(states.size());

	// Calcule de mise en page dynamique des boutons
	float spacing = 50;
	float centerX = 300;
	float firstButtonY = (window.getWindow().getSize().y - (buttonSize.y * buttonCount + spacing * (buttonCount - 1))) / 2.0f; // Dynamique set of buttons

	for (unsigned int i = 0; i < buttonCount; ++i) {
		sf::RectangleShape button(buttonSize);
		button.setFillColor(sf::Color(255, 0, 0)); // Set RGB color
		button.setOrigin(buttonSize.x / 2.0f, buttonSize.y / 2.0f);
		button.setPosition(centerX, firstButtonY + i * (buttonSize.y + spacing));
		mapButton.push_back(button);
		buttonTexts.push_back(setTextOnButton(states[i], mapButton[i], 20));
	}
}

void Menu::update(Window_s& window, Music& music) {
	switch (_MenuState)
	{
	case BASE:
		changeOnMouse(window);
		break;
	case PLAY:
		break;
	case SETTINGS:
		_settings.valueChanger(window, music);
		_settings.changeOnMouse(window);
		break;
	case HELP:
		break;
	case SUCCESS:
		break;
	case CREDIT:
		break;
	case QUIT:
		break;
	default:
		break;
	}



}

void Menu::handleEvent(const sf::Event& event, Window_s &window, Music &music)
{
	// State switcher
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Return) {
			resetValues(window);
			loadMenuButton(window);
			draw(window);
			_MenuState = BASE;
		}
	}

	switch (_MenuState)
	{
	case BASE:
		handleButtonClick(event, window, music);
		break;
	case PLAY:
		break;
	case SETTINGS:
		_settings.handleMouseDrag(event, window);
		break;
	case HELP:
		break;
	case SUCCESS:
		break;
	case CREDIT:
		break;
	case QUIT:
		break;
	default:
		break;
	}

}

void Menu::handleButtonClick(const sf::Event& event, Window_s& window, Music &music) {
	if (event.type != sf::Event::MouseButtonPressed) {
		return;
		if (event.mouseButton.button != sf::Mouse::Left) {
			return;
		}
	}



	sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
	sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);

	for (size_t i = 0; i < buttonTexts.size(); ++i) {
		if (mapButton[i].getGlobalBounds().contains(mousePosF)) {
			std::string buttonText = buttonTexts[i].getString(); // Get the text of the button


			if (buttonText == "PLAY") {
				resetValues(window);
				setMenuState(PLAY);
			}
			else if (buttonText == "SETTINGS") {
				resetValues(window);

				_settings.resetValues(window); // Detruit tout ce quil y a dans les layers et toute les valeurs (les valeurs seront remplacer par les loaders)
				_settings.loadSettings(window); // Load les bouttons de settings
				_settings.draw(window); // Draw les boutons chargé
				_settings.drawSliders(window); // Draw les bouton chargé dans Slider.cpp (creer dans le constructeur et modulé dans HandleEvent) 
				setMenuState(SETTINGS); // Set state for handleEvent
			}
			else if (buttonText == "HELP") {
				resetValues(window);
				setMenuState(HELP);
			}
			else if (buttonText == "SUCCESS") {
				resetValues(window);
				setMenuState(SUCCESS);
			}
			else if (buttonText == "CREDIT") {
				resetValues(window);
				setMenuState(CREDIT);
			}
			else if (buttonText == "QUIT") {
				window.close();
			}
			break;
		}
	}
}

const Menu::MenuStates Menu::getMenuState() const {
	return _MenuState;
}

void Menu::setMenuState(MenuStates MenuState) {
	_MenuState = MenuState;
}

const bool Menu::getIsMenu() const {
	return _isMenu;
}

void Menu::setIsMenu(bool isMenu) {
	_isMenu = isMenu;
}