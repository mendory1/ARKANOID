#include "Brick.h"
#include "Config.h"

Brick::Brick(float x, float y, sf::Color color, int hp) : destroyed(false), health(hp) {
    shape.setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
    shape.setPosition({ x, y });
    shape.setFillColor(color);
}
void Brick::update(float deltaTime) {}
void Brick::draw(sf::RenderWindow& window) { if (!destroyed) window.draw(shape); }
sf::FloatRect Brick::getBounds() const { return shape.getGlobalBounds(); }
bool Brick::isDestroyed() const { return destroyed; }
void Brick::hit(int& score, Game& game) {
    health--;
    score += 1;
    if (health <= 0) destroyed = true;
}
