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
	{"Issu d'une famille de petits notables de la Fert�-Milon et t�t orphelin, Racine re�oit aupr�s des"}, 
	{"Solitaires de Port-Royal une �ducation litt�raire et religieuse rare. Se d�tournant d'une"},
	{"carri�re eccl�siastique, il entreprend, jeune, de faire une carri�re des lettres2, en privil�giant la"},
	{"po�sie et le th��tre tragique. Le succ�s d�Alexandre le Grand, en 1665,"},
	{"lui conf�re une solide r�putation et lui apporte le soutien du jeune roi Louis XIV. Andromaque, en 1667, ouvre une"},
	{"d�cennie de grandes cr�ations qui voit, � c�t� d'une unique com�die (Les Plaideurs, 1668),"},
	{"repr�sent�es les sept trag�dies consacr�es par l�historiographie comme ses plus remarquables :"},
	{"Britannicus (1669), B�r�nice (1670), Bajazet (1672), Mithridate (1673), Iphig�nie (1674) et Ph�dre"},
	{"(1677). La � tristesse majestueuse3 � de ces pi�ces �pur�es rompant avec l�h�ro�sme baroque"},
	{"fait la renomm�e du dramaturge et divise profond�ment le public fran�ais, dont une partie d�fend la trag�die corn�lienne."},
	{"Le succ�s populaire, les querelles critiques,"},
	{"l'appui du roi et les faveurs � la cour de Mme de Montespan entra�nent une ascension sociale et �conomique fulgurante de l'auteur :"},
	{"�lu � l'Acad�mie fran�aise en 1672, anobli en 1674, Racine abandonne en 1677"},
	{"le � m�tier de po�sie � pour briguer le � glorieux emploi4 � d'historiographe du roi. Devenu l'un des courtisans proches du Roi-Soleil,"},
	{" il ne d�laisse son travail d'historien que pour donner, � la demande de Mme de Maintenon,"},
	{"deux trag�dies bibliques aux jeunes filles de Saint-Cyr : Esther (1689) et Athalie (1691), "},
	{" et pour �crire en secret un Abr�g� de l'histoire de Port-Royal, retrouv� et publi� apr�s sa mort. "}
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