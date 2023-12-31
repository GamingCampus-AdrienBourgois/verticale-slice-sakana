#include "Menu.hpp"

Menu::Menu(Window_s& window, Music& music) : _settings(window, music)
{


	// set values
	elapsed = 0;
	_MenuState = BASE;
	_PreviousMenuState = BASE;
	_fontButton.loadFromFile("asset/font/Beyonders.ttf");



}

Menu::~Menu() = default;

void Menu::rainAnim(float deltaTime, Window_s& window)
{
	// utile quand on bouge la fenetre, delta time devine tres grand ce qui bug tout
	const float maxDelta = 0.05f;
	deltaTime = std::min(deltaTime, maxDelta);

	sf::Vector2u winSize = window.getWindow().getSize();
	for (auto& drop : particles)
	{
		drop.move(0, 1000 * deltaTime); // Vitesse de chute
		if (drop.getPosition().y > winSize.y)
		{
			drop.setPosition(static_cast<float>(rand() % winSize.x), -static_cast<float>(rand() % 30)); // Reinitialisation de la goutte
		}
	}
}

void Menu::textureSetters(Window_s& window)
{
	sf::Vector2u windowSize = window.getWindow().getSize();
	float X = static_cast<float>(windowSize.x);
	float Y = static_cast<float>(windowSize.y);

	// load texture and create de sprite 
	std::vector<std::string> globaleFile = {"asset/sprite/menu/background.png", "asset/sprite/menu/logo.png" };

	bgTex.resize(globaleFile.size());
	bgSprt.resize(globaleFile.size());

	for (size_t i = 0; i < globaleFile.size(); i++)
	{
		if (!bgTex[i].loadFromFile(globaleFile[i]))
		{
			throw std::runtime_error("Failed to load texture");
		}
		else
		{
			bgSprt[i].setTexture(bgTex[i]);
		}
	}
	// here we set scale/position/origin
	bgSprt[0].setScale(X / bgTex[0].getSize().x, Y / bgTex[0].getSize().y); // attapt pos to screen size

	bgSprt[1].setScale(sf::Vector2f(0.5f, 0.5f));
	bgSprt[1].setOrigin(sf::Vector2f((bgTex[1].getSize().x) / 2.f, (bgTex[1].getSize().y) / 2.f));
	bgSprt[1].setPosition(X - (X * 0.4f), Y - (Y * 0.75f));

	// load texture on buttons
	buttonTex.resize(buttons.size());

	for (size_t i = 0; i < buttons.size(); i++)
	{
		if (!buttonTex[i].loadFromFile("asset/sprite/menu/woodButton.jpg"))
		{
			throw std::runtime_error("Failed to load texture");
		}
		else
		{
			buttons[i].setTexture(&buttonTex[i]);
		}
	}
}

void Menu::load(Window_s& window)
{
	// load les boutons
	sf::Vector2f buttonSize(300, 75);
	std::vector<std::string> states = {"PLAY", "SETTINGS", "HELP", "SUCCESS", "CREDIT", "QUIT"};

	float spacing = 50;
	float centerX = 300;
	float firstButtonY = (window.getWindow().getSize().y - (buttonSize.y * states.size() + spacing * (states.size() - 1))) / 2.0f; // Dynamique set of buttons

	for (size_t i = 0; i < states.size(); ++i)
	{
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
	for (int i = 0; i < raindrops; ++i)
	{
		sf::RectangleShape drop;
		drop.setSize(sf::Vector2f(1.0f, static_cast<float>(rand() % 5 + 5))); // Taille al�atoire
		drop.setPosition(static_cast<float>(rand() % winSize.x), static_cast<float>(rand() % winSize.y));
		drop.setFillColor(sf::Color(255, 255, 255));
		particles.push_back(drop);
	}

	// load les texture et sprite
	textureSetters(window);
}


void Menu::togglePlayMenu() {
	_MenuState = (_MenuState == BASE) ? PLAY : BASE;
}


const Menu::MenuStates Menu::getMenuState() const
{
	return _MenuState;
}

void Menu::setMenuState(MenuStates MenuState)
{
	_MenuState = MenuState;
}


// STATE APPLYIER OR STATE SWITCHER
// Reload by state, good for settings application
void Menu::reloadByState(Window_s& window)
{
	switch (_MenuState)
	{
	case BASE: reloding(window);
		break;
	case SETTINGS: _settings.reloding(window);
		break;
	case HELP: _help.reloding(window);
		break;
	case SUCCESS: _success.reloding(window);
		break;
	case CREDIT: _credit.reloding(window);
		break;
	case QUIT: break;
	default: break;
	}
}

void Menu::update(Window_s& window, Music& music, float deltaTime)
{
	sf::Vector2i currentPosition = window.getWindow().getPosition();

	switch (_MenuState)
	{
	case BASE: 
		rainAnim(deltaTime, window);
		changeOnMouse(window);
		break;
	case SETTINGS: 
		_settings.valueChanger(window, music);
		_settings.changeOnMouse(window);
		break;
	case HELP:
		break;
	case SUCCESS: 
		_success.update(deltaTime);
		break;
	case CREDIT: 
		_credit.scroller(deltaTime, music);
		break;
	case QUIT:
		break;
	default: break;
	}
}

void Menu::handleEvent(const sf::Event& event, Window_s& window, Music& music)
{
	// State switcher
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Return)
		{
			switch (_MenuState)
			{
			case BASE:  reloding(window);
				music.stopAllMusic();
				music.playMusic(MBASE);
				_MenuState = BASE;
				_PreviousMenuState = BASE;
				break;
			case PLAY: 
				
				reloding(window);
				music.stopAllMusic();
				music.playMusic(MBASE);



				_MenuState = BASE;
				_PreviousMenuState = PLAY;
				break;
			case SETTINGS: reloding(window); // reloaders
				music.stopAllMusic();
				music.playMusic(MBASE);

				_MenuState = BASE; // the state before settings is BASE (globale menu)
				_PreviousMenuState = SETTINGS; // set this, usefull if there are more states in the states for exemple if they is another state in settings
				break;
			case HELP: reloding(window);
				music.stopAllMusic();
				music.playMusic(MBASE);

				_MenuState = BASE;
				_PreviousMenuState = HELP;
				break;
			case SUCCESS: reloding(window);
				music.stopAllMusic();
				music.playMusic(MBASE);

				_MenuState = BASE;
				_PreviousMenuState = SUCCESS;
				break;
			case CREDIT: reloding(window);
				music.stopAllMusic();
				music.playMusic(MBASE);

				_MenuState = BASE;
				_PreviousMenuState = CREDIT;
				break;
			case QUIT:
				// nothing there
				break;
			default: break;
			}
		}
	}

	// Methode that require event
	switch (_MenuState)
	{
	case BASE: handleButtonClick(event, window, music);
		break;
	case SETTINGS: _settings.handleMouseDrag(event, window);
		_settings.handleButtonClick(event, window, music);
		break;
	case HELP: break;
	case SUCCESS: break;
	case CREDIT: break;
	case QUIT: break;
	default: break;
	}
}

void Menu::handleButtonClick(const sf::Event& event, Window_s& window, Music& music)
{
	if (event.type != sf::Event::MouseButtonPressed || event.mouseButton.button != sf::Mouse::Left)
	{
		return;
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(window.getWindow());
	sf::Vector2f mousePosF = window.getWindow().mapPixelToCoords(mousePos);

	for (size_t i = 0; i < buttonTexts.size(); ++i)
	{
		if (buttons[i].getGlobalBounds().contains(mousePosF))
		{
			std::string buttonText = buttonTexts[i].getString(); // Get the text of the button

			if (buttonText == "PLAY")
			{
				resetValues(window);
				music.stopAllMusic();
				music.playMusic(MPLAY);
				setMenuState(PLAY);
			}
			else if (buttonText == "SETTINGS")
			{
				resetValues(window); // reset value for menu only but destroy every layers for drawing
				_settings.reloding(window); // or reload range
				_settings.drawSliders(window); // Draw les bouton chargé dans Slider.cpp (creer dans le constructeur et module dans HandleEvent) 
				music.stopAllMusic();
				music.playMusic(MSETTINGS);
				setMenuState(SETTINGS); // Set state for handleEvent
			}
			else if (buttonText == "HELP")
			{
				resetValues(window);
				_help.reloding(window);
				music.stopAllMusic();
				music.playMusic(MHELP);

				setMenuState(HELP);
			}
			else if (buttonText == "SUCCESS")
			{
				resetValues(window);
				_success.reloding(window);
				music.stopAllMusic();
				music.playMusic(MSUCCESS);

				setMenuState(SUCCESS);
			}
			else if (buttonText == "CREDIT")
			{
				resetValues(window);
				music.stopAllMusic();
				music.playMusic(MCREDIT);
				_credit.reloding(window);

				setMenuState(CREDIT);
			}
			else if (buttonText == "QUIT")
			{
				window.close();
			}
			break;
		}
	}
}
