#include "Ath.hpp"

Ath::Ath(PlayObject& obj) : _obj(obj) {
	totalTime = 0.f;
}

void Ath::load(Window_s& window) {
	totalTime = 0.f;

	window.removeFromRenderLayer(static_cast<int>(Scene::FRONT), _obj.frontSprt[FrontS::BLUR]);
	// Load Map
	if (!_obj.frontTex[FrontS::BLUR].loadFromFile("asset/sprite/fishgame/Blur.png")) {
		throw std::runtime_error("Failed to load");
	}
	_obj._fontAny.loadFromFile("asset/font/Beyonders.ttf");

	sf::RectangleShape timerFrame;
	timerFrame.setSize(sf::Vector2f(400, 150));
	timerFrame.setOrigin(timerFrame.getSize().x / 2.0f, timerFrame.getSize().y / 2.0f);

	timerFrame.setFillColor(sf::Color(0, 0, 0, 150));
	timerFrame.setOutlineColor(sf::Color::White);
	timerFrame.setOutlineThickness(2);


	sf::Vector2u windowSize = window.getWindow().getSize();
	_obj.globalRec[RectS::FRAME] = timerFrame;


	sf::Text timerText;
	timerText.setFont(_obj._fontAny);
	timerText.setCharacterSize(48);

	timerText.setFillColor(sf::Color::Black);



	_obj.globalTexts[TextS::TIMER] = timerText;


}


void Ath::clock(float deltaTime, Window_s& window, sf::View& cameraView) {
	totalTime += deltaTime;

	int seconds = static_cast<int>(totalTime);
	_obj.globalTexts[TextS::TIMER].setString(std::to_string(seconds) + " s");
	_obj.globalTexts[TextS::TIMER].setOrigin(
		_obj.globalTexts[TextS::TIMER].getLocalBounds().width / 2.0f,
		_obj.globalTexts[TextS::TIMER].getLocalBounds().height / 2.0f
	);

	sf::Vector2f viewSize = cameraView.getSize();
	sf::Vector2f viewCenter = cameraView.getCenter();
	sf::Vector2f timerPosition = sf::Vector2f(viewCenter.x + viewSize.x / 2 - 300, viewCenter.y - viewSize.y / 2 + 100);




	_obj.globalTexts[TextS::TIMER].setPosition(timerPosition);
	_obj.globalRec[RectS::FRAME].setPosition(timerPosition);


}



void Ath::pause(Window_s& window, sf::View& cameraView) {
	sf::Vector2u windowSize = window.getWindow().getSize();
	float X = static_cast<float>(windowSize.x);
	float Y = static_cast<float>(windowSize.y);

	_obj.frontSprt[FrontS::BLUR].setTexture(_obj.frontTex[FrontS::BLUR]);
	float scaleX5 = X / _obj.frontTex[FrontS::BLUR].getSize().x * 2.0f;
	float scaleY5 = Y / _obj.frontTex[FrontS::BLUR].getSize().y * 2.0f;

	_obj.frontSprt[FrontS::BLUR].setScale(scaleX5, scaleY5);

	_obj.frontSprt[FrontS::BLUR].setOrigin(_obj.frontTex[FrontS::BLUR].getSize().x / 2.f, _obj.frontTex[FrontS::BLUR].getSize().y / 2.f);
	_obj.frontSprt[FrontS::BLUR].setPosition(cameraView.getCenter());








	window.placeInLayerAt(static_cast<int>(Scene::FRONT), _obj.frontSprt[FrontS::BLUR], FrontS::BLUR);
}

void Ath::unpause(Window_s& window) {
	window.removeFromRenderLayer(static_cast<int>(Scene::FRONT), _obj.frontSprt[FrontS::BLUR]);
}