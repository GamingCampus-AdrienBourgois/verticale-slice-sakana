#pragma once
#include<map>
#include<vector>
#include<string>
#include"Bouton.h"


class Menu {
	std::string nameMenu;
	sf::Texture* texture;
	sf::Sprite* background;
	std::vector<Bouton*> vect_boutons;
	std::map<std::string, std::vector<Bouton*>> lesboutons ; //= std::map<std::string, std::vector<Bouton*>>();

public:
	Menu() = default;
	
	Menu(std::string name_m,std::string texturepath);
	~Menu();

	void addBouton(std::string etiquette, float xpos=0.f, float ypos=0.f);

	void insertBouton(Bouton b);

};