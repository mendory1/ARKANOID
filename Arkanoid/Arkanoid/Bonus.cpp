#include "Bonus.h"
#include "Config.h"

Bonus::Bonus(sf::Vector2f pos, sf::Color color) : active(true) {
    shape.setRadius(8.f);
    shape.setFillColor(color);
    shape.setPosition(pos);
}
void Bonus::update(float deltaTime) {
    if (!active) return;
    shape.move({ 0.f, 150.f * deltaTime });
    if (shape.getPosition().y > WINDOW_HEIGHT) active = false;
}
void Bonus::draw(sf::RenderWindow& window) { if (active) window.draw(shape); }
sf::FloatRect Bonus::getBounds() const { return shape.getGlobalBounds(); }
bool Bonus::isActive() const { return active; }
void Bonus::deactivate() { active = false; }
