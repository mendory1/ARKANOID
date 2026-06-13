#pragma once
#include <vector>
#include <memory>

class Ball;
class Racket;
class Field;
class Bonus;
class Game;

class CollisionSystem {
public:
    static void handleAllCollisions(std::vector<std::unique_ptr<Ball>>& balls, Racket& racket, Field& field, std::vector<std::unique_ptr<Bonus>>& bonuses, int& score, Game& game);
};
