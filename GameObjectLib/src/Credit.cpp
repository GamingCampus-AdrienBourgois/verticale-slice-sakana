#include "Credit.hpp"

Credit::Credit() : elapsed(0.0f)
{
	_fontButton.loadFromFile("asset/font/Beyonders.ttf");
	_fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
}

void Credit::textureSetters(Window_s& window) {
    sf::Vector2u windowSize = window.getWindow().getSize();
    float X = static_cast<float>(windowSize.x);
    float Y = static_cast<float>(windowSize.y);

    // load texture and create de sprite 
    std::vector<std::string> globaleFile = { "asset/sprite/credit/background.png" };

    bgTex.resize(globaleFile.size());
    bgSprt.resize(globaleFile.size());

    for (size_t i = 0; i < globaleFile.size(); i++) {
        if (!bgTex[i].loadFromFile(globaleFile[i])) {
            throw std::runtime_error("Failed to load texture");
        }
        else {
            bgSprt[i].setTexture(bgTex[i]);
        }
    }
    // here we set scale/position/origin
    bgSprt[0].setScale(X / bgTex[0].getSize().x, Y / bgTex[0].getSize().y); // attapt pos to screen size

}

void Credit::load(Window_s& window)
{
    std::vector<std::string> creditString = {
    {"Credits de Sakana Man"},
    {"Developpeur principal :"},
    {"Labady Marcus"},
    {""},
    {"Equipe de developpement :"},
    {"Stremler Franck /  Gittou Roussi Maxime - Concepteur de jeu - Concepteur de jeu"},
    {"Galland Shayan - Programmeur principal"},
    {"Stremler Franck - Artiste principal"},
    {"Mirabella Enzo / Lesluin Adrien / Cardoso Florian - Designer de niveaux"},
    {"Labady Marcus - Musicien et compositeur"},
    {""},
    {"Conception graphique :" },
    {"Stremler Franck - Directeur artistique"},
    {"Stremler Franck - Illustrateur"},
    {"Stremler Franck - Animateur"},
    {""},
    {"Programmation:"},
    {"Galland Shayan / Gittou Roussi Maxime - Programmeur de gameplay"},
    {"Galland Shayan - Programmeur d'IA"},
    {""},
    {"Art et Animation : "},
    {"Stremler Franck - Artiste de personnages"},
    {"Stremler Franck - Artiste d'environnement"},
    {""},
    {"Son et Musique :"},
    {"Labady Marcus - Concepteur sonore"},
    {"Labady Marcus - Compositeur de musique originale"},
    {""},
    {"Testeurs du jeu " },
    {"Galland Shayan "},
    {"Cardoso Florian "},
    {"Stremler Franck "},
    {"Gittou Roussi Maxime"},
    {"Lesluin Adrien"},
    {"Labady Marcus"},
    {"Mirabella Enzo"},
    {""},
    {"Gestion de projet :" },
    {"Stremler Franck - Chef de projet"},
    {""},
    {"Remerciements speciaux :" },
    {"Nous tenons a exprimer notre gratitude a tous ceux qui ont soutenu ce projet, que ce soit par des encouragements, des retours constructifs ou des contributions."},
    {""},
    {"Droits d'auteur :"},
    {"2023 SakanaCorp"},
    {""},
    {"Merci infiniment à notre incroyable communaute de joueurs pour votre soutien continu. SakanaMan  ne serait pas le meme sans vous."},
    {"Gros big Up a Marcus le GOAT"}
    };


	float spacing = 50;

	for (size_t i = 0; i < creditString.size(); ++i) {
		sf::Text creditText = createText(creditString[i], sf::Vector2f(static_cast<float>(window.getWindow().getSize().x) / 2, static_cast<float>(window.getWindow().getSize().y) + (spacing * i)), 15, sf::Color(255, 255, 255));
		globalTexts.push_back(creditText);
	}

    textureSetters(window);
}

void Credit::scroller(float deltaTime, Music& music) {
	if (globalTexts[globalTexts.size() - 1].getPosition().y + 50 <= 0)
		return;
	float speed = 80.0f;

	elapsed += deltaTime;
	if (elapsed >= 0.01f) {
		for (size_t i = 0; i < globalTexts.size(); ++i) {
			globalTexts[i].move(0, -speed * deltaTime);
		}
		elapsed = 0.0f;
	}
}