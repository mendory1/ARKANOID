#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Field;
class Racket;
class Ball;
class Bonus;

class RenderSystem {
private:
    static void drawPixelGameOver(sf::RenderWindow& window);
    static void drawPixelWin(sf::RenderWindow& window);
public:
    static void renderGame(
        sf::RenderWindow& window,
        Field& field,
        Racket& racket,
        const std::vector<std::unique_ptr<Ball>>& balls,
        const std::vector<std::unique_ptr<Bonus>>& bonuses,
        int score,
        int lives,
        bool isGameOver,
        bool isVictory
    );
};
