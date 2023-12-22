#include "Window.hpp"
#include <iostream>
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
    window.clear(sf::Color(61, 37, 59));
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



void Window_s::addToRenderLayer(int layer, const sf::Drawable& drawable) {
    _renderLayers[layer].emplace_back(&drawable, std::nullopt); // No render states
}


void Window_s::addToRenderLayer(int layer, const sf::Drawable& drawable, const sf::RenderStates& state) {
    _renderLayers[layer].emplace_back(&drawable, state);
}


void Window_s::removeFromRenderLayer(int layer, const sf::Drawable& drawable) {
    auto& pairs = _renderLayers[layer];
    for (size_t i = 0; i < pairs.size(); ++i) {
        if (pairs[i].first == &drawable) {
            _deletedIndices[layer].insert(i);
            pairs.erase(pairs.begin() + i);
            break;
        }
    }
}

int Window_s::countDeletionsInRange(int layer, size_t startIndex, size_t endIndex) {
    int count = 0;
    if (_deletedIndices.find(layer) != _deletedIndices.end()) {
        for (size_t i = startIndex; i <= endIndex; ++i) {
            if (_deletedIndices[layer].find(i) != _deletedIndices[layer].end()) {
                count++;
            }
        }
    }
    return count;
}


    void Window_s::renderLayers() {
        for (const auto& [layer, pairs] : _renderLayers) {
            for (const auto& [drawable, optionalState] : pairs) {
                if (optionalState) {
                    window.draw(*drawable, *optionalState);
                }
                else {
                    window.draw(*drawable);
                }
            }
        }
    }

    void Window_s::replaceFromRenderLayer(int layer, const sf::Drawable& oldDrawable, const sf::Drawable& newDrawable, const sf::RenderStates& state) {
        auto& pairs = _renderLayers[layer];
        for (auto& pair : pairs) {
            if (pair.first == &oldDrawable) {
                pair = std::make_pair(&newDrawable, state);
                break;
            }
        }
    }

    void Window_s::placeInLayerAt(int layer, const sf::Drawable& drawable, size_t position) {
        if (_renderLayers.find(layer) == _renderLayers.end()) {
            std::cerr << "Error layer does not exist" << std::endl;
        }

        if (position <= _renderLayers[layer].size()) {
            _renderLayers[layer].insert(_renderLayers[layer].begin() + position, std::make_pair(&drawable, std::nullopt));
        }
        else {
            _renderLayers[layer].emplace_back(&drawable, std::nullopt);
        }
    }


void Window_s::resetView() {
    sf::FloatRect visibleArea(0, 0, static_cast<float>(this->getWindow().getSize().x), static_cast<float>(this->getWindow().getSize().y));
    this->getWindow().setView(sf::View(visibleArea));
}

