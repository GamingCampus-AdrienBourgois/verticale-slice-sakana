#include "PlayObject.hpp"
#include <iostream>
sf::Text PlayObject::createText(const std::string& text, const sf::Vector2f& position, unsigned int size, sf::Color color)
{
	sf::Text textObject;
	textObject.setFont(_fontAny);
	textObject.setString(text);
	textObject.setCharacterSize(size);
	textObject.setFillColor(color);
	textObject.setPosition(position);
	sf::FloatRect bounds = textObject.getLocalBounds();
	textObject.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	return textObject;
}



void PlayObject::draw(Window_s& window)
{


	for (size_t i = 0; i < globalRec.size(); i++)
		window.addToRenderLayer(static_cast<int>(Scene::RECTGB), globalRec[i]);
	for (size_t i = 0; i < globalSprt.size(); i++)
		window.addToRenderLayer(static_cast<int>(Scene::SPRITESGB), globalSprt[i]);
	for (size_t i = 0; i < globalTexts.size(); i++)
		window.addToRenderLayer(static_cast<int>(Scene::TEXTGB), globalTexts[i]);
	for (size_t i = 0; i < bgSprt.size(); i++)
		window.addToRenderLayer(static_cast<int>(Scene::SPRITESBG), bgSprt[i]);
	for (size_t i = 0; i < bgRec.size(); i++)
		window.addToRenderLayer(static_cast<int>(Scene::RECTBG), bgRec[i]);
	for (size_t i = 0; i < frontSprt.size(); i++)
		window.addToRenderLayer(static_cast<int>(Scene::FRONT), frontSprt[i]);




	for (size_t i = 0; i < massSprt.size(); i++)
	{
		for (size_t j = 0; j < massSprt[i].size(); j++)
		{
			window.addToRenderLayer(static_cast<int>(Scene::SPRITESMASS), massSprt[i][j]);
		}
	}
	

}

void PlayObject::resetValues(Window_s& window)
{
	globalRec.clear();
	globalTex.clear();
	globalSprt.clear();
	globalTexts.clear();
	bgTex.clear();
	bgSprt.clear();
	bgRec.clear();
	frontSprt.clear();
	frontTex.clear();

	for (size_t i = 0; i < massSprt.size(); i++)
	{
		massSprt[i].clear();
	}

	window.clearLayer(static_cast<int>(Scene::SPRITESBG));
	window.clearLayer(static_cast<int>(Scene::RECTBG));
	window.clearLayer(static_cast<int>(Scene::SPRITESGB));
	window.clearLayer(static_cast<int>(Scene::RECTGB));
	window.clearLayer(static_cast<int>(Scene::TEXTGB));
	window.clearLayer(static_cast<int>(Scene::FRONT));
	window.clearLayer(static_cast<int>(Scene::SPRITESMASS));

	globalSprt.resize(GlobalS::GEND);
	globalTex.resize(GlobalS::GEND);
	bgSprt.resize(BackS::BEND);
	bgTex.resize(BackS::BEND);
	frontTex.resize(FrontS::FEND);
	frontSprt.resize(FrontS::FEND);
	globalTexts.resize(TextS::TEND);
	globalRec.resize(RectS::REEND);
}