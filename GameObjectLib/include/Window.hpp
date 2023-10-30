#pragma once
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

class Window_s {
public:
    Window_s(unsigned int width = 1600, unsigned int height = 1000, const std::string& title = "SFML Window");

    void addToRenderLayer(int layer, const sf::Drawable& drawable);
    void removeFromRenderLayer(int layer, const sf::Drawable& drawable);
    void renderLayers();

    bool isOpen() const;
    void close();
    void clear();
    void display();
    bool pollEvent(sf::Event& event);
    sf::RenderWindow& getWindow() {
        return window;
    }

private:
    std::map<int, std::vector<const sf::Drawable*>> _renderLayers; // layer 1 = path, layer 2 = wall, layer 3 = hero, layer 4 = monster
    sf::RenderWindow window;
};