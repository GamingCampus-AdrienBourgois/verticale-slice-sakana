#include "Help.hpp"

Help::Help() {
    buttonCount = 0;
    _fontButton.loadFromFile("asset/font/Beyonders.ttf");
    _fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
}

void Help::load(Window_s& window) {
    std::vector<std::string> helpString = {
        {"Les pingouins sont un groupe de oiseaux aquatiques non volants qui vivent"},
        {"principalement dans l'hémisphère sud. Contrairement aux idées reçues, les pingouins"},
        {"ne se trouvent pas seulement en Antarctique mais aussi sur les côtes de l'Afrique du Sud,"},
        {"de l'Amérique du Sud, de l'Australie et même sur certaines îles plus tempérées."},
        {"Ces oiseaux sont particulièrement adaptés à la vie aquatique, avec leur corps fuselé"},
        {"et leurs ailes transformées en nageoires. Leur plumage dense les aide à résister au froid."},
        {"Les pingouins se nourrissent principalement de poissons, de krill et d'autres"},
        {"formes de vie marine, qu'ils capturent en plongeant dans l'eau."},
        {"Les espèces de pingouins varient en taille, du petit manchot pygmée"},
        {"d'une trentaine de centimètres au grand manchot empereur pouvant atteindre"},
        {"jusqu'à un mètre de hauteur. Ces oiseaux ont un comportement social remarquable,"},
        {"avec des rituels de parade nuptiale élaborés et un fort instinct de groupe pour la"},
        {"protection contre les prédateurs et pour la chaleur dans les climats froids."},
        {"Ils sont souvent perçus comme des animaux curieux et sympathiques, ce qui en fait"},
        {"des sujets populaires dans la culture et les médias. Malheureusement, plusieurs espèces"},
        {"de pingouins sont menacées par des facteurs environnementaux comme le réchauffement climatique,"},
        {"la pollution et la pêche industrielle, qui réduit leurs sources de nourriture."}
    };


	float spacing = 50;

	for (size_t i = 0; i < helpString.size(); ++i) {
		sf::Text helpText = createText(helpString[i], sf::Vector2f(window.getWindow().getSize().x / 2, 40 + (i * spacing)), 18);
		basicTexts.push_back(helpText);
	}
}