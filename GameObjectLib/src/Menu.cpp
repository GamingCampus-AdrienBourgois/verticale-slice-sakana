#include "Menu.hpp"

Menu::Menu() : _isMenu(true), _MenuState(BASE), buttonCount(0)//, _settings()
{
	_font.loadFromFile("asset/font/Beyonders.ttf");
}

Menu::~Menu() = default;

void Menu::draw(Window_s& window) {
	for (unsigned int i = 0; i < buttonCount; i++) {
		window.addToRenderLayer(2, buttonTexts[i]); // Add text on buttons
		window.addToRenderLayer(1, mapButton[_MenuState][i]); // Add buttons
	}
}

void Menu::LoadMenuButton(Window_s& window)
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

sf::Text Menu::setTextOnButton(const std::string& text, sf::RectangleShape& button) {
	sf::Color color(0, 255, 0);
	sf::Text buttonText(text, _font, 20); // Taille de texte 20
	buttonText.setFillColor(color);
	sf::FloatRect textRect = buttonText.getLocalBounds();
	buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	buttonText.setPosition(button.getPosition());
	return buttonText;
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

void Menu::resetValues(Window_s& window) {
	buttonTexts.clear();
	for (auto& stateButtons : mapButton) {
		stateButtons.second.clear();
	}
	buttonCount = 0;
	window.clearLayer(1);
	window.clearLayer(2);
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