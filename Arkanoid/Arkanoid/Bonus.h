#pragma once
#include "Entity.h"

class Bonus : public Entity {
private:
    sf::CircleShape shape;
    int type;
    bool active;
public:
    Bonus(sf::Vector2f pos, int t);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;

    bool isActive() const { return active; }
    void deactivate() { active = false; }
    int getType() const { return type; }
};
