#include "PlayObject.hpp"
#include <iostream>

PlayObject::PlayObject() {
	globalSprt.resize(GlobalS::GEND);
	globalTex.resize(GlobalS::GEND);
	bgSprt.resize(BackS::BEND);
	bgTex.resize(BackS::BEND);
	frontTex.resize(FrontS::FEND);
	frontSprt.resize(FrontS::FEND);

	globalTexts.resize(TextS::TEND);
	globalRec.resize(RectS::REEND);
}

bool PlayObject::checkPixelCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
	sf::FloatRect intersection;
	if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds(), intersection)) {
		sf::IntRect rect1 = sprite1.getTextureRect();
		sf::IntRect rect2 = sprite2.getTextureRect();

		sf::Image image1 = sprite1.getTexture()->copyToImage();
		sf::Image image2 = sprite2.getTexture()->copyToImage();

		for (int i = static_cast<int>(intersection.left); i < intersection.left + intersection.width; ++i) {
			for (int j = static_cast<int>(intersection.top); j < intersection.top + intersection.height; ++j) {

				sf::Vector2f sprite1Pos = sprite1.getInverseTransform().transformPoint(static_cast<float>(i), static_cast<float>(j));
				sf::Vector2f sprite2Pos = sprite2.getInverseTransform().transformPoint(static_cast<float>(i), static_cast<float>(j));

				if (sprite1Pos.x > 0 && sprite1Pos.y > 0 && sprite1Pos.x < rect1.width && sprite1Pos.y < rect1.height &&
					sprite2Pos.x > 0 && sprite2Pos.y > 0 && sprite2Pos.x < rect2.width && sprite2Pos.y < rect2.height) {

					sf::Color color1 = image1.getPixel(static_cast<unsigned int>(sprite1Pos.x + rect1.left), static_cast<unsigned int>(sprite1Pos.y + rect1.top));
					sf::Color color2 = image2.getPixel(static_cast<unsigned int>(sprite2Pos.x + rect2.left), static_cast<unsigned int>(sprite2Pos.y + rect2.top));

					if (color1.a != 0 && color2.a != 0) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

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




	for (int i = 0; i < static_cast<int>(massSprt.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(massSprt[i].size()); j++)
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

	for (int i = 0; i < static_cast<int>(massSprt.size()); i++)
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