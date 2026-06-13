#pragma once
#include "Bonus.h"

class BonusBottom : public Bonus {
public:
    BonusBottom(sf::Vector2f pos);
    void activateEffect(Game& game) override;
};
