#pragma once
#include <SFML/Graphics.hpp>
#include "Window.hpp"


enum class Scene {
	SPRITESBG = 1,
	RECTBG,
	SPRITESGB,
	RECTGB,
	TEXTGB
};

class PlayObject {

	virtual void load(Window_s &window) = 0;

	sf::Text createText(const std::string& text, const sf::Vector2f& position, unsigned int size, sf::Color color)
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

	void reloding(Window_s& window)
	{
		resetValues(window); // Detruit tout ce quil y a dans les layers et toute les valeurs (les valeurs seront remplacer par les loaders)
		load(window); // Load les bouttons
		draw(window); // Draw les boutons chargé
	}

	void draw(Window_s& window)
	{
		for (size_t i = 0; i < globalRec.size(); i++)
		{
			window.addToRenderLayer(static_cast<int>(Scene::RECTGB), globalRec[i]);
		}
		for (size_t i = 0; i < globalSprt.size(); i++)
		{
			window.addToRenderLayer(static_cast<int>(Scene::SPRITESGB), globalSprt[i]);
		}
		for (size_t i = 0; i < globalTexts.size(); i++)
		{
			window.addToRenderLayer(static_cast<int>(Scene::TEXTGB), globalTexts[i]);
		}
		for (size_t i = 0; i < bgSprt.size(); i++)
		{
			window.addToRenderLayer(static_cast<int>(Scene::SPRITESBG), bgSprt[i]);
		}
		for (size_t i = 0; i < bgRec.size(); i++)
		{
			window.addToRenderLayer(static_cast<int>(Scene::RECTBG), bgRec[i]);
		}

	}

	void resetValues(Window_s& window)
	{
		globalRec.clear();
		globalSprt.clear();
		globalTexts.clear();
		bgSprt.clear();
		bgRec.clear();

		window.clearLayer(static_cast<int>(Scene::SPRITESBG));
		window.clearLayer(static_cast<int>(Scene::RECTBG));
		window.clearLayer(static_cast<int>(Scene::SPRITESGB));
		window.clearLayer(static_cast<int>(Scene::RECTGB));
		window.clearLayer(static_cast<int>(Scene::TEXTGB));
	}

protected:
	sf::Font _fontAny; // font for anything

	std::vector<sf::RectangleShape> globalRec; // rectangle shape for anything
	std::vector<sf::Texture> globalTex; // texture for all the sprites
	std::vector<sf::Sprite> globalSprt; // sprites for anything (first plan)
	std::vector<sf::Text> globalTexts; // texts for anything

	std::vector<sf::Texture> bgTex; // texture for background sprites
	std::vector<sf::Sprite> bgSprt; // sprites for background (second plan)
	std::vector<sf::RectangleShape> bgRec; // rectangle shape for any background effect like rain
};
