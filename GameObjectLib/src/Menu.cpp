#include "Menu.hpp"

Menu::Menu(Window_s& window, Music& music) : _settings(window, music), _credit(), _help(), _success(), _play()
{
	// set values
	elapsed = 0;
	_isMenu = true;
	_MenuState = BASE;
	_PreviousMenuState = BASE;
	buttonCount = 0;
	_fontButton.loadFromFile("asset/font/Beyonders.ttf");
}

Menu::~Menu() = default;


void Menu::rainAnim(float deltaTime, Window_s &window)
{
	// utile quand on bouge la fenetre, delta time devine tres grand ce qui bug tout
	const float maxDelta = 0.05f;
	deltaTime = std::min(deltaTime, maxDelta);

	sf::Vector2u winSize = window.getWindow().getSize();
	for (auto& drop : particles) {
		drop.move(0, 1000 * deltaTime); // Vitesse de chute
		if (drop.getPosition().y > winSize.y) {
			drop.setPosition(static_cast<float>(rand() % winSize.x), -static_cast<float>(rand() % 30)); // R�initialisation de la goutte
		}
	}
}

void Menu::textureSetters(Window_s &window)
{
	sf::Vector2u windowSize = window.getWindow().getSize();
	float X = static_cast<float>(windowSize.x);
	float Y = static_cast<float>(windowSize.y);

	// load texture and create de sprite 
	std::vector<std::string> globaleFile = { "asset/sprite/menu/background.png" };

	bgTex.resize(globaleFile.size());
	bgSprt.resize(globaleFile.size());

	for (size_t i = 0; i < globaleFile.size(); i++) {
		if (!bgTex[i].loadFromFile(globaleFile[i])) {
			throw std::runtime_error("Failed to load texture");
		} else {
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
		} else {
			buttons[i].setTexture(&buttonTex[i]);
		}
	}
}

void Menu::load(Window_s& window)
{
	// load les boutons
	sf::Vector2f buttonSize(300, 75);
	std::vector<std::string> states = { "PLAY", "SETTINGS", "HELP", "SUCCESS", "CREDIT", "QUIT" };
	buttonCount = static_cast<unsigned int>(states.size());

	float spacing = 50;
	float centerX = 300;
	float firstButtonY = (window.getWindow().getSize().y - (buttonSize.y * buttonCount + spacing * (buttonCount - 1))) / 2.0f; // Dynamique set of buttons

	for (unsigned int i = 0; i < buttonCount; ++i) {
		sf::RectangleShape button(buttonSize);
		button.setFillColor(sf::Color(255, 0, 0)); // Set RGB color
		button.setOrigin(buttonSize.x / 2.0f, buttonSize.y / 2.0f);
		button.setPosition(centerX, firstButtonY + i * (buttonSize.y + spacing));
		button.setOutlineThickness(1);
		buttons.push_back(button);
		buttonTexts.push_back(setTextOnButton(states[i], buttons[i], 20, sf::Color(0, 255, 0)));
	}

	// load des gouttes de pluie
	sf::Vector2u winSize = window.getWindow().getSize();
	for (int i = 0; i < raindrops; ++i) {
		sf::RectangleShape drop;
		drop.setSize(sf::Vector2f(1.0f, static_cast<float>(rand() % 5 + 5))); // Taille al�atoire
		drop.setPosition(static_cast<float>(rand() % winSize.x), static_cast<float>(rand() % winSize.y));
		drop.setFillColor(sf::Color(255, 255, 255));
		particles.push_back(drop);
	}
	std::cout << "prok";
	// load les texture et sprite
	textureSetters(window);
}

void Menu::update(Window_s& window, Music& music, float deltaTime) {
	sf::Vector2i currentPosition = window.getWindow().getPosition();

	switch (_MenuState)
	{
	case BASE:
		rainAnim(deltaTime, window);
		changeOnMouse(window);
		break;
	case PLAY:
		break;
	case SETTINGS:
		_settings.valueChanger(window, music);
		_settings.changeOnMouse(window);
		break;
	case HELP:
		// none
		break;
	case SUCCESS:
		_success.update(deltaTime);
		break;
	case CREDIT:
		_credit.scroller(deltaTime, music);
		break;
	case QUIT:
		// none
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
			
			switch (_MenuState)
			{
			case BASE:

				_MenuState = BASE;
				_PreviousMenuState = BASE;
				break;
			case PLAY:
				reloding(window);
				_isMenu = true;
				_MenuState = BASE;
				_PreviousMenuState = PLAY;
				break;
			case SETTINGS:
				// reloaders
				reloding(window);

				// the state before settings is BASE (globale menu)
				_MenuState = BASE;
				// set this, usefull if there are more states in the states for exemple if they is another state in settings
				_PreviousMenuState = SETTINGS;
				break;
			case HELP:
				reloding(window);

				_MenuState = BASE;
				_PreviousMenuState = HELP;
				break;
			case SUCCESS:
				reloding(window);

				_MenuState = BASE;
				_PreviousMenuState = SUCCESS;
				break;
			case CREDIT:
				reloding(window);

				music.stopMusic(MCREDIT);
				music.playMusic(MBASE);

				_MenuState = BASE;
				_PreviousMenuState = CREDIT;
				break;
			case QUIT:
				// nothing there
				break;
			default:
				break;
			}

		}
	}

	// Methode that require event
	switch (_MenuState)
	{
	case BASE:
		handleButtonClick(event, window, music);
		break;
	case PLAY:
		break;
	case SETTINGS:
		_settings.handleMouseDrag(event, window);
		_settings.handleButtonClick(event, window, music);
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
	if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left) {
		return;
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
	sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);

	for (size_t i = 0; i < buttonTexts.size(); ++i) {
		if (buttons[i].getGlobalBounds().contains(mousePosF)) {
			std::string buttonText = buttonTexts[i].getString(); // Get the text of the button

			if (buttonText == "PLAY") {
				resetValues(window);
				_isMenu = true;
				setMenuState(PLAY);
			}
			else if (buttonText == "SETTINGS") {
				resetValues(window); // reset value for menu only but destroy every layers for drawing

				_settings.reloding(window);
				// or reload range
				_settings.drawSliders(window); // Draw les bouton charg� dans Slider.cpp (creer dans le constructeur et modul� dans HandleEvent) 
				setMenuState(SETTINGS); // Set state for handleEvent
			}
			else if (buttonText == "HELP") {
				resetValues(window);
				_help.reloding(window);
				setMenuState(HELP);
			}
			else if (buttonText == "SUCCESS") {
				resetValues(window);
				_success.reloding(window);
				setMenuState(SUCCESS);
			}
			else if (buttonText == "CREDIT") {
				resetValues(window);

				music.stopMusic(MBASE);
				music.playMusic(MCREDIT);
				_credit.reloding(window);
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