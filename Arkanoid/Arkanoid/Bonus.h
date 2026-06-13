#pragma once
#include "Entity.h"

class Bonus : public Entity {
protected:
    sf::CircleShape shape;
    bool active = true;
public:
    Bonus(sf::Vector2f pos, sf::Color color);
    virtual ~Bonus() = default;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;

    bool isActive() const;
    void deactivate();
    virtual void activateEffect(Game& game) override = 0;
};
