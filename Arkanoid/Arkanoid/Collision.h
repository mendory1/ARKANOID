#pragma once
#include <SFML/Graphics.hpp>

class Racket;
class Ball;
class Field;
class Bonus;
class Game;

void handleAllCollisions(Racket& racket, std::vector<std::unique_ptr<Ball>>& balls, Field& field, std::vector<std::unique_ptr<Bonus>>& bonuses, int& score, Game& game);

inline bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b) {
    return a.findIntersection(b).has_value();
}