#pragma once
#include <string>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>

class Window_s {
public:
    // Constructor - Destructor
    Window_s(unsigned int width = 200, unsigned int height = 150, const std::string& title = "Window");
    ~Window_s();

    // Functions
    void run();
    void toggleFullscreen();
    void zoom(float factor);
    void resetZoom();
    void moveView(const sf::Vector2f& offset);

    // Layer
    void addToRenderLayer(int layer, const sf::Drawable& drawable);
    void removeFromRenderLayer(int layer, const sf::Drawable& drawable);
    void renderLayers();

    // Setters
    void setFrame(int frame);
    void setVerticalSyncEnabled(bool enabled);
    void setTitle(const std::string& title);
    void setSize(unsigned int width, unsigned int height);

    // Getters
    bool isOpen() const;
    bool isVerticalSyncEnabled() const;
    bool hasFocus() const;
    int getFrame();
    std::string getTitle() const;
    sf::Vector2u getSize() const;
    sf::Vector2i getMousePosition() const;

private:
    bool _isOpen;
    bool _isVSyncEnable;
    bool isFullscreen;

    int _frame;


    sf::Vector2f windowDim;
    sf::RenderWindow window;
    sf::View view;

    std::string _title;

    std::map<int, std::vector<const sf::Drawable*>> _renderLayers;
};
