#pragma once
#include "Bonus.h"

class BonusBall : public Bonus {
public:
    BonusBall(sf::Vector2f pos);
    void activateEffect(Game& game) override;
};
