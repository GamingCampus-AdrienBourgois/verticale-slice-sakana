#include<iostream>
#include"SFML/Window.hpp"
#include"Bouton.hpp"

Bouton::Bouton(std::string etiquette, float x, float y) {

	//sf::Vector2f origin_text, size_text;
	//cadre = new sf::RectangleShape();
	textBouton = new sf::Text();
	if (!font.loadFromFile("asset/Zombie_Sunday.otf")) {
		//delete cadre;
		delete textBouton;
		//cadre = nullptr;
		std::cout << "Erreur de font" << std::endl;
		return;
	}

	/*font et taille des caracteres du texte du bouton*/
	intitule = etiquette;
	textBouton->setFont(font);
	textBouton->setString(intitule);
	textBouton->setCharacterSize(24);
	textBouton->setPosition(x, y);
	click = false;

	/*taille du cadre*/
	//cadre->setSize(sf::Vector2f(120.f, 80.f));

	/*position du cadre*/
	//cadre->setPosition(sf::Vector2f(x, y));

	/*position du texte par rapport à celle du cadre*/
	//textBouton->setPosition(cadre->getPosition().x + (cadre->getSize().x / 2),
		//cadre->getPosition().y + (cadre->getPosition().y / 2));


	/*on met le point d'origine du texte au centre de celui-ci*/
	//origin_text = textBouton.getOrigin();
	//textBouton.setOrigin(origin_text + textBouton.getL)
	
}

Bouton::~Bouton() {
	//delete cadre;
	delete textBouton;
	//cadre = nullptr;
	textBouton = nullptr;

}


void Bouton::drawBouton(sf::RenderWindow* w) {
	//w->draw(*cadre);
	w->draw(*textBouton);
}


void Bouton::assignAction(void* f) {
	return;
}


void Bouton::onClick(sf::Mouse* m, sf::RenderWindow* f) {
	sf::Vector2f souris_pos = static_cast<sf::Vector2f>(m->getPosition(*f));

	if (textBouton->getGlobalBounds().contains(souris_pos)) {
		if (m->isButtonPressed(sf::Mouse::Left) || m->isButtonPressed(sf::Mouse::Right)) {
			std::cout << "vous avez cliquez sur le bouton\n" << std::endl;
		}
	}
}


void Bouton::setPosition(float x, float y) {
	//cadre->setPosition(x, y);
	//textBouton->setPosition(/*cadre->getPosition().*/x + (cadre->getSize().x / 2),
		/*cadre->getPosition().*/ //y + (cadre->getPosition().y / 2));

	textBouton->setPosition(x, y);
}

void Bouton::setPosition(sf::Vector2f p) {
	/*cadre->setPosition(p.x, p.y);
	textBouton->setPosition(cadre->getPosition().x + (cadre->getSize().x / 2),
		cadre->getPosition().y + (cadre->getPosition().y / 2));*/
	textBouton->setPosition(p);
}

/*epaisseur du bouton*/
void Bouton::setThickness(float t) {
	textBouton->setOutlineThickness(t);
}

/*couleur de fond du bouton*/
void Bouton::setColorBouton(sf::Color c) {
	textBouton->setOutlineColor(c);
}

void Bouton::setColorTextBouton(sf::Color c) {
	textBouton->setFillColor(c);
}
