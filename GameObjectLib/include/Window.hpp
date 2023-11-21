#pragma once
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

class Window_s {
public:
    Window_s(unsigned int width = 1600, unsigned int height = 1000, const std::string& title = "SFML Window");
    ~Window_s() = default;

    // Layers functions
    void addToRenderLayer(int layer, const sf::Drawable& drawable);
    void removeFromRenderLayer(int layer, const sf::Drawable& drawable);
    void renderLayers();
    void clearLayer(int layer);

    bool isOpen() const;
    void close();
    void clear();
    bool pollEvent(sf::Event& event);
    sf::RenderWindow& getWindow();
    void display();
private:
    std::map<int, std::vector<const sf::Drawable*>> _renderLayers; // Layer assigment :
    sf::RenderWindow window;
};