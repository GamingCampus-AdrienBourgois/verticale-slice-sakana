#include "Window.hpp"

Window_s::Window_s(unsigned int width, unsigned int height, const std::string& title) 
    : window(sf::VideoMode(width, height), title) {
    window.setFramerateLimit(60);
}

bool Window_s::isOpen() const {
    return window.isOpen();
}

void Window_s::close() {
    window.close();
}

void Window_s::clear() {
    window.clear();
}

void Window_s::display() {
    window.display();
}

bool Window_s::pollEvent(sf::Event& event) {
    return window.pollEvent(event);
}

void Window_s::addToRenderLayer(int layer, const sf::Drawable& drawable)
{
    _renderLayers[layer].push_back(&drawable);
}

void Window_s::removeFromRenderLayer(int layer, const sf::Drawable& drawable)
{
    auto& drawables = _renderLayers[layer];
    drawables.erase(std::remove(drawables.begin(), drawables.end(), &drawable), drawables.end());
}

void Window_s::renderLayers()
{
    for (const auto& [layer, drawables] : _renderLayers) {
        for (const auto& drawable : drawables) {
            window.draw(*drawable);
        }
    }
}