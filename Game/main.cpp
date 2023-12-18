#include <iostream>
#include <random>
#include <time.h>

#include "../GameObjectLib/include/GameLoop.hpp"

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	GameLoop game;
	game.run();
	return 0;
}


/*
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Eraser");

    sf::Texture texture;
    if (!texture.loadFromFile("asset/sprite/fishgame/map.jpg")) {
        // Handle error
    }

    sf::RenderTexture renderTexture;
    if (!renderTexture.create(texture.getSize().x, texture.getSize().y)) {
        // Handle error
    }

    renderTexture.clear(sf::Color::Transparent);
    renderTexture.draw(sf::Sprite(texture));
    renderTexture.display();

    sf::Shader shader;
    if (!shader.loadFromFile("erase.frag", sf::Shader::Fragment)) {
        // Handle error
    }

    shader.setUniform("texture", sf::Shader::CurrentTexture);
    float eraserRadius = 20.0f; // Example radius

    bool erase = false; // Flag to check if erasing should occur

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update shader uniform for mouse position
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(pixelPos.x, window.getSize().y - pixelPos.y));
        shader.setUniform("mouse", sf::Glsl::Vec2(worldPos.x, worldPos.y));
        shader.setUniform("radius", eraserRadius);

        // Render the texture with the shader
        sf::Sprite sprite(renderTexture.getTexture());
        window.clear(sf::Color::Red);
        window.draw(sprite, &shader);
        window.display();
    }

    return 0;
}


   */