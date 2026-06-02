#include "Bonus.h"
#include "Config.h"

Bonus::Bonus(sf::Vector2f pos, int t) : type(t), active(true) {
    shape.setRadius(8.f);
    shape.setPosition(pos);
    if (type == 5) shape.setFillColor(sf::Color::Magenta);
    else if (type == 6) shape.setFillColor(sf::Color::Yellow);
    else shape.setFillColor(sf::Color::Cyan);
}
void Bonus::update(float deltaTime) {
    if (!active) return;
    shape.move({ 0.f, 150.f * deltaTime });
    if (shape.getPosition().y > WINDOW_HEIGHT) active = false;
}
void Bonus::draw(sf::RenderWindow& window) { if (active) window.draw(shape); }
sf::FloatRect Bonus::getBounds() const { return shape.getGlobalBounds(); }
