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
        {"Issu d'une famille de petits notables de la Fert�-Milon et t�t orphelin, Racine re�oit aupr�s des"},
        {"Solitaires de Port-Royal une �ducation litt�raire et religieuse rare. Se d�tournant d'une"},
        {"carri�re eccl�siastique, il entreprend, jeune, de faire une carri�re des lettres, en privil�giant la"},
        {"po�sie et le th��tre tragique. Le succ�s d�Alexandre le Grand, en 1665,"},
        {"lui conf�re une solide r�putation et lui apporte le soutien du jeune roi Louis XIV. Andromaque, en 1667, ouvre une"},
        {"d�cennie de grandes cr�ations qui voit, � c�t� d'une unique com�die (Les Plaideurs, 1668),"},
        {"repr�sent�es les sept trag�dies consacr�es par l�historiographie comme ses plus remarquables :"},
        {"Britannicus (1669), B�r�nice (1670), Bajazet (1672), Mithridate (1673), Iphig�nie (1674) et Ph�dre"},
        {"(1677). La tristesse majestueuse de ces pi�ces �pur�es rompant avec l�h�ro�sme baroque"},
        {"fait la renomm�e du dramaturge et divise profond�ment le public fran�ais, dont une partie d�fend la trag�die corn�lienne."},
        {"Le succ�s populaire, les querelles critiques,"},
        {"l'appui du roi et les faveurs � la cour de Mme de Montespan entra�nent une ascension sociale et �conomique fulgurante de l'auteur :"},
        {"�lu � l'Acad�mie fran�aise en 1672, anobli en 1674, Racine abandonne en 1677"},
        {"le m�tier de po�sie pour briguer le glorieux emploi d'historiographe du roi. Devenu l'un des courtisans proches du Roi-Soleil,"},
        {" il ne d�laisse son travail d'historien que pour donner, � la demande de Mme de Maintenon,"},
        {"deux trag�dies bibliques aux jeunes filles de Saint-Cyr : Esther (1689) et Athalie (1691), "},
        {" et pour �crire en secret un Abr�g� de l'histoire de Port-Royal, retrouv� et publi� apr�s sa mort. "},
        {"Le vaste travail historique auquel il consacre la majeure partie de ses vingt derni�res ann�es,"},
        {"l'histoire de Louis XIV, dispara�t enti�rement dans l'incendie de la maison de son successeur, Valincour."},
        {"L'�uvre de Racine passe pour avoir amen� la trag�die classique � son accomplissement et son harmonie5. "},
        {"L'�conomie du propos, la rigueur de la construction (situation de crise men�e � son acm�),"},
        {"la ma�trise de l'alexandrin et la profondeur de l'analyse psychologique ont �lev� le corpus racinien"},
        {"au rang de mod�le classique. Par son respect strict des unit�s de temps, de lieu et d'action,"},
        {"Racine refuse la primaut�, la densit� et l'h�ro�sme de l'action propres aux trag�dies de Pierre Corneille,"},
        {"auquel il est souvent oppos�. Il lui pr�f�re un �purement de l'intrigue (parfois extr�me, en particulier dans B�r�nice)"},
        {"et l'intensit� psychologique. Abandonnant le ton glorieux et moral du th��tre du d�but du xviie si�cle,"},
        {"Racine soumet la vertu politique et la raison d'�tat, ch�res � Corneille, sous les contingences passionnelles."},
        {"La passion soumet et d�truit ses personnages tout-puissants (rois, empereurs, princesses) qui tentent en vain"},
        {"de lutter contre elle, perdant le sens du devoir jusqu'� la d�raison ou la mort."},
        {"Les passions, parmi lesquelles l'amour prime, sont le fondement du tragique racinien en ce qu'ils sont les instruments du destin."},
        {"L'amour racinien suit en ordre g�n�ral la structure du triangle amoureux, inexorable et cruel pour chacun des partis."},
        {"Le fondement de ce tragique rel�ve � ce titre de la confrontation de la d�mesure et de la d�raison des passions"},
        {"avec l'humilit� de la finitude des mortels. Les trag�dies de Racine se fondent sur la conjonction"},
        {"de la crainte et de la piti� (les deux �motions fondamentales du th��tre antique) ; la critique a souvent estim�"},
        {"que le dramaturge a ainsi cherch� � associer la pr�destination jans�niste et le fatum antique."},
        {"Consacr� par la critique comme l'un des plus grands auteurs fran�ais de trag�dies, il est l'un des trois dramaturges majeurs,"},
        {"avec Corneille et Moli�re, de la p�riode classique en France. Aujourd'hui, il compte parmi les auteurs"},
        {"les plus jou�s � la Com�die-Fran�aise et dans le pays, et figure parmi les grandes r�f�rences"},
        {"de la litt�rature universelle."}
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