#include "BrickSpeed.h"
#include "Game.h"

class Ball;

SpeedUpBrick::SpeedUpBrick(float x, float y) : Brick(x, y, sf::Color::Red, 1) {}
void SpeedUpBrick::hit(int& score, Game& game) {
    Brick::hit(score, game);
    if (destroyed) {
        game.accelerateActiveBalls();
    }
}
