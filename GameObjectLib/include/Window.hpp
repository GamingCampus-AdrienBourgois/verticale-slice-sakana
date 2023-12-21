#pragma once
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <optional>
#include <set>

class Window_s {
public:
    Window_s(const std::string& title);
    ~Window_s() = default;

    // Layers functions
    void addToRenderLayer(int layer, const sf::Drawable& drawable);
    void addToRenderLayer(int layer, const sf::Drawable& drawable, const sf::RenderStates& state);
    void removeFromRenderLayer(int layer, const sf::Drawable& drawable);
    void renderLayers();
    void clearLayer(int layer);
    void replaceFromRenderLayer(int layer, const sf::Drawable& oldDrawable, const sf::Drawable& newDrawable, const sf::RenderStates& state = sf::RenderStates::Default);
    void placeInLayerAt(int layer, const sf::Drawable& drawable, size_t position);
    int countDeletionsInRange(int layer, size_t startIndex, size_t endIndex);





    bool isOpen() const;
    void close();
    void clear();
    bool pollEvent(sf::Event& event);
    sf::RenderWindow& getWindow();
    void display();


    const std::string &getTitle() const;
    void setFps(unsigned int fps);
    const unsigned int getFps() const;
    void resetView();


private:
    std::map<int, std::vector<std::pair<const sf::Drawable*, std::optional<sf::RenderStates>>>> _renderLayers;

    std::map<int, std::set<size_t>> _deletedIndices;



    sf::RenderWindow window;
    unsigned int _fps;
    std::string _title;
};