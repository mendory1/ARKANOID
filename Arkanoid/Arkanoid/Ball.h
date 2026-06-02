#pragma once
#include "Entity.h"

class Ball : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    bool active;
public:
    Ball(sf::Vector2f startPos, sf::Vector2f startVel, sf::Color color = sf::Color::Cyan);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;

    bool isActive() const { return active; }
    void deactivate() { active = false; }
    void bounceX() { velocity.x = -velocity.x; }
    void bounceY() { velocity.y = -velocity.y; }
    void setVelocity(sf::Vector2f vel) { velocity = vel; }
    void multiplyVelocity(float factor) { velocity *= factor; }
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    void setPosition(sf::Vector2f pos) { shape.setPosition(pos); }
};
