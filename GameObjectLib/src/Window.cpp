#include "Window.hpp"

Window_s::Window_s(const std::string& title) 
    : window(sf::VideoMode(1600, 900), title), _fps(60), _title(title) {
    window.setFramerateLimit(_fps);
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

sf::RenderWindow& Window_s::getWindow() {
    return window;
}

void Window_s::setFps(unsigned int fps) {
    window.setFramerateLimit(fps);
    _fps = fps;
}

const unsigned int Window_s::getFps() const {
    return _fps;
}

const std::string& Window_s::getTitle() const {
    return _title;
}


void Window_s::clearLayer(int layer) {
    if (_renderLayers.find(layer) != _renderLayers.end()) {
        _renderLayers[layer].clear();
    }
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