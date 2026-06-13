#include "BrickIndestructible.h"

IndestructibleBrick::IndestructibleBrick(float x, float y) : Brick(x, y, sf::Color(128, 128, 128), 1) {}
void IndestructibleBrick::hit(int& score, Game& game) {}
