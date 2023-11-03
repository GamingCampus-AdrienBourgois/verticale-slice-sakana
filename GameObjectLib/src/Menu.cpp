#include<iostream>
#include "Menu.hpp"


Menu::Menu(std::string name_m,std::string texturepath) {
	nameMenu = name_m;
	texture = new sf::Texture();
	background = new sf::Sprite();
	//lesboutons = std::map<std::string, std::vector<Bouton>>();

	if (!texture->loadFromFile(texturepath)) {
		std::cout << "Erreur chargement texture\n";
		delete texture;
		delete background;
		//delete lesboutons;
		return;
	}
}


Menu::~Menu() {
	delete texture;
	delete background;
	//delete les elements du map
	//delete lesboutons;
}


void Menu::addBouton(std::string etiquette, float xpos, float ypos) {
	Bouton* b = new Bouton(etiquette, xpos, ypos);
	std::vector<Bouton*>* vect_bouton = new std::vector<Bouton*>();
	vect_bouton->push_back(b);
	lesboutons[nameMenu] = vect_bouton;
}

void insertBouton(Bouton b) {

}