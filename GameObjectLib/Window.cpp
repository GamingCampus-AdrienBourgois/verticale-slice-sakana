#include "Window.hpp"

Window_s::Window_s(unsigned int width, unsigned int height, const std::string& title) : _isOpen(true), _isVSyncEnable(false), isFullscreen(false), _frame(60), window(sf::VideoMode(width, height), title), _title(title), _renderLayers(NULL, NULL)
{
    windowDim.x = width;
    windowDim.y = height;
    view = window.getDefaultView();
}

Window_s::~Window_s()
{
    window.close();
}

void Window_s::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
}

void Window_s::toggleFullscreen()
{
    isFullscreen = !isFullscreen;
    window.close();

    if (isFullscreen) {
        window.create(sf::VideoMode::getDesktopMode(), getTitle(), sf::Style::Fullscreen);
    }
    else {
        window.create(sf::VideoMode(windowDim.x, windowDim.y), getTitle());
    }
}

void Window_s::zoom(float factor)
{
    view.zoom(factor);
    window.setView(view);
}

void Window_s::resetZoom()
{
    view.setSize(window.getDefaultView().getSize());
    view.setCenter(window.getDefaultView().getCenter());
    window.setView(view);
}

void Window_s::moveView(const sf::Vector2f& offset)
{
    view.move(offset);
    window.setView(view);
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
    for (const auto& pair : _renderLayers) {
        int layer = pair.first;
        const auto& drawables = pair.second;
        for (const auto& drawable : drawables) {
            window.draw(*drawable);
        }
    }

}

//setters and getters
bool Window_s::hasFocus() const
{
    return window.hasFocus();
}

void Window_s::setVerticalSyncEnabled(bool enabled)
{
    window.setVerticalSyncEnabled(enabled);
    _isVSyncEnable = enabled;
}

bool Window_s::isVerticalSyncEnabled() const
{
    return _isVSyncEnable;
}

void Window_s::setFrame(int frame)
{
    window.setFramerateLimit(frame);
    _frame = frame;
}

int Window_s::getFrame() {
    return _frame;
}

sf::Vector2u Window_s::getSize() const
{
    return window.getSize();
}

void Window_s::setSize(unsigned int width, unsigned int height)
{
    window.setSize(sf::Vector2u(width, height));
}

std::string Window_s::getTitle() const
{
    return _title;
}

void Window_s::setTitle(const std::string& title)
{
    window.setTitle(title);
}

bool Window_s::isOpen() const
{
    return _isOpen;
}

sf::Vector2i Window_s::getMousePosition() const
{
    return sf::Mouse::getPosition(window);
}