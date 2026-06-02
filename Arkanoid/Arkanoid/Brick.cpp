#include "Brick.h"

Brick::Brick(float x, float y, BlockType t) : type(t), destroyed(false) {
    shape.setSize({ BLOCK_WIDTH, BLOCK_HEIGHT });
    shape.setPosition({ x, y });
    health = (type == BlockType::Durability) ? 3 : 1;

    switch (type) {
    case BlockType::Indestructible: shape.setFillColor(sf::Color(128, 128, 128)); break;
    case BlockType::WithBonus: shape.setFillColor(sf::Color::Yellow); break;
    case BlockType::SpeedUp: shape.setFillColor(sf::Color::Red); break;
    case BlockType::Durability: shape.setFillColor(sf::Color::Blue); break;
    default: shape.setFillColor(sf::Color::Green); break;
    }
}
void Brick::update(float deltaTime) {}
void Brick::draw(sf::RenderWindow& window) { if (!destroyed) window.draw(shape); }
sf::FloatRect Brick::getBounds() const { return shape.getGlobalBounds(); }
void Brick::hit(int& score) {
    if (type == BlockType::Indestructible) return;
    health--;
    score += 1;
    if (health <= 0) destroyed = true;
}
