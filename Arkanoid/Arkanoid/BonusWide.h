#pragma once
#include "Bonus.h"

class BonusWide : public Bonus {
public:
    BonusWide(sf::Vector2f pos);
    void activateEffect(Game& game) override;
};
