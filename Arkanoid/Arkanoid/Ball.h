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

    bool isActive() const;
    void deactivate();
    void bounceX();
    void bounceY();
    void setVelocity(sf::Vector2f vel);
    void multiplyVelocity(float factor);
    sf::Vector2f getPosition() const;
};
