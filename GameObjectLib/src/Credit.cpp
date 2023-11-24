#include "Credit.hpp"

Credit::Credit() : elapsed(0.0f)
{
	buttonCount = 0;
	_fontButton.loadFromFile("asset/font/Beyonders.ttf");
	_fontAny.loadFromFile("asset/font/Dragon Slayer.ttf");
}

void Credit::load(Window_s& window)
{
	std::vector<std::string> creditString = { 
	{"Issu d'une famille de petits notables de la Ferté-Milon et tôt orphelin, Racine reçoit auprès des"}, 
	{"Solitaires de Port-Royal une éducation littéraire et religieuse rare. Se détournant d'une"},
	{"carrière ecclésiastique, il entreprend, jeune, de faire une carrière des lettres2, en privilégiant la"},
	{"poésie et le théâtre tragique. Le succès d’Alexandre le Grand, en 1665,"},
	{"lui confère une solide réputation et lui apporte le soutien du jeune roi Louis XIV. Andromaque, en 1667, ouvre une"},
	{"décennie de grandes créations qui voit, à côté d'une unique comédie (Les Plaideurs, 1668),"},
	{"représentées les sept tragédies consacrées par l’historiographie comme ses plus remarquables :"},
	{"Britannicus (1669), Bérénice (1670), Bajazet (1672), Mithridate (1673), Iphigénie (1674) et Phèdre"},
	{"(1677). La « tristesse majestueuse3 » de ces pièces épurées rompant avec l’héroïsme baroque"},
	{"fait la renommée du dramaturge et divise profondément le public français, dont une partie défend la tragédie cornélienne."},
	{"Le succès populaire, les querelles critiques,"},
	{"l'appui du roi et les faveurs à la cour de Mme de Montespan entraînent une ascension sociale et économique fulgurante de l'auteur :"},
	{"élu à l'Académie française en 1672, anobli en 1674, Racine abandonne en 1677"},
	{"le « métier de poésie » pour briguer le « glorieux emploi4 » d'historiographe du roi. Devenu l'un des courtisans proches du Roi-Soleil,"},
	{" il ne délaisse son travail d'historien que pour donner, à la demande de Mme de Maintenon,"},
	{"deux tragédies bibliques aux jeunes filles de Saint-Cyr : Esther (1689) et Athalie (1691), "},
	{" et pour écrire en secret un Abrégé de l'histoire de Port-Royal, retrouvé et publié après sa mort. "}
	};

	float spacing = 50;

	for (size_t i = 0; i < creditString.size(); ++i) {
		sf::Text creditText = createText(creditString[i], sf::Vector2f(window.getWindow().getSize().x / 2, window.getWindow().getSize().y + (spacing * i)), 18);
		basicTexts.push_back(creditText);
	}
}

void Credit::scroller(float deltaTime, Music& music) {
	if (basicTexts[basicTexts.size() - 1].getPosition().y <= 0)
		return;
	float speed = 100.0f;

	elapsed += deltaTime;
	if (elapsed >= 0.001f) {
		for (size_t i = 0; i < basicTexts.size(); ++i) {
			basicTexts[i].move(0, -speed * deltaTime);
		}
		elapsed = 0.0f;
	}
}