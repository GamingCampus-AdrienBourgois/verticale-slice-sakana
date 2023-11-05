#include<iostream>
#include "Menu.hpp"
#include"Bouton.hpp"

Menu::Menu(std::string name_m,std::string texturepath) {
	nameMenu = name_m;
	texture = new sf::Texture();
	background = new sf::Sprite();
	vect_boutons = new std::vector<Bouton*>();
	lesboutons = std::map<std::string, std::vector<Bouton*>*>();

	if (!texture->loadFromFile(texturepath)) {
		std::cout << "Erreur chargement texture\n";
		delete texture;
		delete background;
		delete vect_boutons;
		return;
	}
	lesboutons[nameMenu] = vect_boutons;

}


Menu::~Menu() {
	delete texture;
	delete background;
	//delete vect_boutons;
	//delete vect_boutons;
	//delete les elements de la 2e partie du map
}


void Menu::addBouton(std::string etiquette, float xpos, float ypos) {
	Bouton* b = new Bouton(etiquette, xpos, ypos);
	vect_boutons->push_back(b);
	
	
	
	/*
	std::vector<Bouton*>* vect_bouton = new std::vector<Bouton*>();
	vect_bouton->push_back(b);
	lesboutons[nameMenu] = vect_bouton;
	*/
}

void insertBouton(Bouton b) {

}