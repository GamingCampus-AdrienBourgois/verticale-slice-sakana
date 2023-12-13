#pragma once
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

class Window_s {
public:
    Window_s(const std::string& title);
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


    const std::string &getTitle() const;
    void setFps(unsigned int fps);
    const unsigned int getFps() const;

private:
    std::map<int, std::vector<const sf::Drawable*>> _renderLayers; 

    sf::RenderWindow window;
    unsigned int _fps;
    std::string _title;
};