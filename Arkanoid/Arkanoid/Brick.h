#pragma once
#include "Entity.h"
#include "Config.h"

class Brick : public Entity {
private:
    sf::RectangleShape shape;
    BlockType type;
    int health;
    bool destroyed;
public:
    Brick(float x, float y, BlockType t);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;

    bool isDestroyed() const { return destroyed; }
    BlockType getType() const { return type; }
    void hit(int& score);
};
