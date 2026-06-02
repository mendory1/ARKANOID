#include "Racket.h"
#include "Config.h"

Racket::Racket() {
    speed = PADDLE_SPEED;
    reset();
}
void Racket::reset() {
    shape.setSize({ PADDLE_WIDTH, PADDLE_HEIGHT });
    shape.setFillColor(sf::Color::White);
    shape.setPosition({ WINDOW_WIDTH / 2.f - PADDLE_WIDTH / 2.f, WINDOW_HEIGHT - 50.f });
}
void Racket::update(float deltaTime) {}
void Racket::draw(sf::RenderWindow& window) { window.draw(shape); }
sf::FloatRect Racket::getBounds() const { return shape.getGlobalBounds(); }
void Racket::moveLeft(float deltaTime) {
    if (shape.getPosition().x > 0) shape.move({ -speed * deltaTime, 0.f });
}
void Racket::moveRight(float deltaTime) {
    if (shape.getPosition().x + shape.getSize().x < WINDOW_WIDTH) shape.move({ speed * deltaTime, 0.f });
}
void Racket::expand() { shape.setSize({ PADDLE_WIDTH * 1.5f, PADDLE_HEIGHT }); }
sf::Vector2f Racket::getPosition() const { return shape.getPosition(); }
sf::Vector2f Racket::getSize() const { return shape.getSize(); }
