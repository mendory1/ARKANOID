#include "BonusWide.h"
#include "Game.h"
#include "Racket.h"

BonusWide::BonusWide(sf::Vector2f pos) : Bonus(pos, sf::Color::Magenta) {}
void BonusWide::activateEffect(Game& game) { game.getRacket().expand(); }
