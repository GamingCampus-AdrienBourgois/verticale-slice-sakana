#include "Help.hpp"

Help::Help() {
    _fontButton.loadFromFile("asset/font/Beyonders.ttf");
    _fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
}

void Help::textureSetters(Window_s& window) {
    sf::Vector2u windowSize = window.getWindow().getSize();
    float X = static_cast<float>(windowSize.x);
    float Y = static_cast<float>(windowSize.y);

    // load texture and create de sprite 
    std::vector<std::string> globaleFile = { "asset/sprite/help/background.png" };

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

void Help::load(Window_s& window) {
    std::vector<std::string> helpString = {
        {"Les pingouins sont un groupe de oiseaux aquatiques non volants qui vivent"},
        {"principalement dans l'h�misph�re sud. Contrairement aux id�es re�ues, les pingouins"},
        {"ne se trouvent pas seulement en Antarctique mais aussi sur les c�tes de l'Afrique du Sud,"},
        {"de l'Am�rique du Sud, de l'Australie et m�me sur certaines �les plus temp�r�es."},
        {"Ces oiseaux sont particuli�rement adapt�s � la vie aquatique, avec leur corps fusel�"},
        {"et leurs ailes transform�es en nageoires. Leur plumage dense les aide � r�sister au froid."},
        {"Les pingouins se nourrissent principalement de poissons, de krill et d'autres"},
        {"formes de vie marine, qu'ils capturent en plongeant dans l'eau."},
        {"Les esp�ces de pingouins varient en taille, du petit manchot pygm�e"},
        {"d'une trentaine de centim�tres au grand manchot empereur pouvant atteindre"},
        {"jusqu'� un m�tre de hauteur. Ces oiseaux ont un comportement social remarquable,"},
        {"avec des rituels de parade nuptiale �labor�s et un fort instinct de groupe pour la"},
        {"protection contre les pr�dateurs et pour la chaleur dans les climats froids."},
        {"Ils sont souvent per�us comme des animaux curieux et sympathiques, ce qui en fait"},
        {"des sujets populaires dans la culture et les m�dias. Malheureusement, plusieurs esp�ces"},
        {"de pingouins sont menac�es par des facteurs environnementaux comme le r�chauffement climatique,"},
        {"la pollution et la p�che industrielle, qui r�duit leurs sources de nourriture."}
    };


	float spacing = 50;

	for (size_t i = 0; i < helpString.size(); ++i) {
		sf::Text helpText = createText(helpString[i], sf::Vector2f(window.getWindow().getSize().x / 2, 40 + (i * spacing)), 18, sf::Color(0, 0, 0));
		globalTexts.push_back(helpText);
	}

    textureSetters(window);
}