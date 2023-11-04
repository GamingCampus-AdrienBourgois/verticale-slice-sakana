#include "Character.hpp"

Character::Character(const std::string& texturePath) {
    _texture.loadFromFile(texturePath);
    _sprite.setTexture(_texture);
    _currentFrame = 0;
    _elapsedTime = 0.0f;
    _direction = Directions::DOWN;
    _animate = true;

    _sprite.setOrigin(FRAME_WIDTH / 2, FRAME_HEIGHT);

}

void Character::update(float deltaTime) {
    if (_animate) {
        _elapsedTime += deltaTime;
        if (_elapsedTime >= FRAME_DURATION) {
            _currentFrame = (_currentFrame + 1) % ANIMATION_FRAMES;
            _elapsedTime -= FRAME_DURATION;
        }
        _sprite.setTextureRect(sf::IntRect(_currentFrame * FRAME_WIDTH, _direction * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
    }
}

void Character::stop() {
    _animate = false;
    _currentFrame = 0; // set to the first frame
    _sprite.setTextureRect(sf::IntRect(_currentFrame * FRAME_WIDTH, _direction * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
}

void Character::draw(Window_s& window) {
    window.addToRenderLayer(3, _sprite);
}




void Character::setPosition(float x, float y)
{
    _sprite.setPosition(x, y);
}

sf::Vector2f Character::getPosition() const {
    return _sprite.getPosition();
}

void Character::setDirection(Directions direction) {
    _animate = true;
    _direction = direction;
}

void Character::setSize(float x, float y) {
    _sprite.setScale(x, y);
}

sf::FloatRect Character::getFeetBoundsAtPosition(float x, float y) const {
    // Ne jamais toucher a ca, horrible et illogique a comprendre
    sf::IntRect textureRect = _sprite.getTextureRect();

    float feetHeight = textureRect.height * 0.4f; // 40% de la hauteur du personnage

    // Réduire la largeur de la hitbox par un certain pourcentage
    float adjustedWidth = textureRect.width * 0.5f;
    float widthOffset = (textureRect.width - adjustedWidth) / 5; // Pour centrer la hitbox

    float additionalOffset = textureRect.width * 0.5f;
    widthOffset -= additionalOffset;

        
    //
    float adjustedY = y - textureRect.height + feetHeight;

    return sf::FloatRect(x + widthOffset, adjustedY, adjustedWidth, feetHeight);
}




void Character::move(const sf::Event& event, const Labyrinth& labyrinth) {
    if (event.type == sf::Event::KeyPressed) {
        sf::Vector2f futurePosition = getPosition();

        switch (event.key.code) {
        case sf::Keyboard::Up:
            setDirection(Directions::UP);
            futurePosition.y -= 50;
            if (!labyrinth.isCollidingWithWalls(getFeetBoundsAtPosition(futurePosition.x, futurePosition.y))) {
                setPosition(futurePosition.x, futurePosition.y);
            }
            break;
        case sf::Keyboard::Down:
            setDirection(Directions::DOWN);
            futurePosition.y += 50;
            if (!labyrinth.isCollidingWithWalls(getFeetBoundsAtPosition(futurePosition.x, futurePosition.y))) {
                setPosition(futurePosition.x, futurePosition.y);
            }
            break;
        case sf::Keyboard::Left:
            setDirection(Directions::LEFT);
            futurePosition.x -= 50;
            if (!labyrinth.isCollidingWithWalls(getFeetBoundsAtPosition(futurePosition.x, futurePosition.y))) {
                setPosition(futurePosition.x, futurePosition.y);
            }
            break;
        case sf::Keyboard::Right:
            setDirection(Directions::RIGHT);
            futurePosition.x += 50;
            if (!labyrinth.isCollidingWithWalls(getFeetBoundsAtPosition(futurePosition.x, futurePosition.y))) {
                setPosition(futurePosition.x, futurePosition.y);
            }
            break;
        default:
            stop();
            break;
        }
    }
    else if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Up ||
            event.key.code == sf::Keyboard::Down ||
            event.key.code == sf::Keyboard::Left ||
            event.key.code == sf::Keyboard::Right) {
            stop();
        }
    }
}
