#include "BrickBonus.h"
#include "Game.h"
#include "Config.h"

BonusBrick::BonusBrick(float x, float y) : Brick(x, y, sf::Color::Yellow, 1) {}
void BonusBrick::hit(int& score, Game& game) {
    Brick::hit(score, game);
    if (destroyed) {
        game.spawnRandomBonus({ shape.getPosition().x + BLOCK_WIDTH / 2, shape.getPosition().y });
    }
}
