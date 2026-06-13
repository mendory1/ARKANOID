#pragma once
#include "Entity.h"

class Brick : public Entity {
protected:
    sf::RectangleShape shape;
    int health;
    bool destroyed;
public:
    Brick(float x, float y, sf::Color color, int hp = 1);
    virtual ~Brick() = default;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    bool isDestroyed() const;
    virtual void hit(int& score, Game& game);
    virtual bool isRequiredForWin() const { return true; }
};
