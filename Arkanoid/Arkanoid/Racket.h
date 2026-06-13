#pragma once
#include "Entity.h"

class Racket : public Entity {
private:
    sf::RectangleShape shape;
    float speed;
public:
    Racket();
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);
    void expand();
    void reset();
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
};
