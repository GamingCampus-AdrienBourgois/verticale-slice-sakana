#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

#include "Window.hpp"

class Menu {
public:
	Menu() : _isMenu(true), _MenuState(BASE)
	{

	}
	~Menu() = default;


	enum MenuStates
	{
		BASE,
		SETTINGS,
		HELP,
		PLAY,
		SUCCESS,
		CREDIT,
		QUIT
	};



	void filMapButton(Window_s &window) {
		sf::RectangleShape button;

		sf::Color col(255, 0, 0);
		button.setSize(sf::Vector2f(100, 50)); // Taille du bouton
		button.setPosition(100, 100); // Position du bouton
		button.setFillColor(col); // Couleur du bouton


		// Ajoutez ce bouton au map pour l'état BASE
		mapButton[BASE].push_back(button);


		for (auto& BaseButton : mapButton[BASE]) {
			window.addToRenderLayer(1, BaseButton);
		}


	}

	void statesGestion() 
	{

	}





	const MenuStates getMenuState() const {
		return _MenuState;
	}
	void setMenuState(MenuStates MenuState) {
		_MenuState = MenuState;
	}

	const bool getIsMenu() const {
		return _isMenu;
	}
	void setIsMenu(bool isMenu) {
		_isMenu = isMenu;
	}
private:
	bool _isMenu;
	MenuStates _MenuState;

	std::map<MenuStates, std::vector<sf::RectangleShape>> mapButton;
};