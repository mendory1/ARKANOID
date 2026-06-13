#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Racket;
class Ball;
class Field;
class Bonus;

class Game {
private:
    sf::RenderWindow window;

    std::unique_ptr<Racket> racket;
    std::vector<std::unique_ptr<Ball>> balls;
    std::unique_ptr<Field> field;
    std::vector<std::unique_ptr<Bonus>> bonuses;

    int score;
    int lives;
    bool isGameOver;
    bool isVictory;

    void processEvents();
    void update(float deltaTime);
    void resetLevel();
    bool checkWinCondition();

    void drawPixelGameOver();
    void drawPixelWin();

public:
    Game();
    ~Game();
    void run();

    Racket& getRacket();
    Field& getField();
    void addBall(std::unique_ptr<Ball> ball);
    void spawnRandomBonus(sf::Vector2f pos);
    void accelerateActiveBalls();
};
