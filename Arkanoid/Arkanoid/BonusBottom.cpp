#include "BonusBottom.h"
#include "Game.h"
#include "Field.h"

BonusBottom::BonusBottom(sf::Vector2f pos) : Bonus(pos, sf::Color::Yellow) {}
void BonusBottom::activateEffect(Game& game) { game.getField().activateExtraBottom(); }
