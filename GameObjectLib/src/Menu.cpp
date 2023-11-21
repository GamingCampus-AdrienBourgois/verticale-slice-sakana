#include "Menu.hpp"

Menu::Menu() : _settings()
{
	_isMenu = true;
	_MenuState = BASE;
	buttonCount = 0;
	_font.loadFromFile("asset/font/Beyonders.ttf");
}

Menu::~Menu() = default;


void Menu::loadMenuButton(Window_s& window)
{
	setMenuState(BASE);
	sf::Vector2f buttonSize(200, 50);
	std::vector<std::string> states = { "PLAY", "SETTINGS", "HELP", "SUCCESS", "CREDIT", "QUIT" };
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
		mapButton[BASE].push_back(button);
		buttonTexts.push_back(setTextOnButton(states[i], mapButton[BASE][i]));
	}
}

void Menu::handleButtonClick(Window_s& window, Music &music) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
	sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);

	for (size_t i = 0; i < buttonTexts.size(); ++i) {
		if (mapButton[_MenuState][i].getGlobalBounds().contains(mousePosF)) {
			std::string buttonText = buttonTexts[i].getString(); // Get the text of the button


			if (buttonText == "PLAY") {
				resetValues(window);
				setMenuState(PLAY);
			}
			else if (buttonText == "SETTINGS") {
				resetValues(window);
				_settings.resetValues(window);
				_settings.loadSettings(window); // Charger les boutons de Settings
				_settings.draw(window);
				setMenuState(SETTINGS);
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

void Menu::update(Window_s& window) {
	changeOnMouse(window);
	_settings.changeOnMouse(window);

}

const Menu::MenuStates Menu::getMenuState() const {
	return _MenuState;
}

void Menu::setMenuState(MenuStates MenuState) {
	_MenuState = MenuState;
}