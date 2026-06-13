#include "Game.h"
#include "Racket.h"
#include "Ball.h"
#include "Field.h"
#include "Bonus.h"
#include "BonusFactory.h"
#include "Brick.h"
#include "Config.h"
#include "Collision.h"
#include "CollisionSystem.h"
#include "RenderSystem.h"
#include <cmath>
#include <string>

Game::Game() : window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Arkanoid"), score(0), lives(3), isGameOver(false), isVictory(false) {
    window.setFramerateLimit(60);

    racket = std::make_unique<Racket>();
    field = std::make_unique<Field>();

    resetLevel();
}

Game::~Game() = default;

void Game::resetLevel() {
    racket->reset();
    balls.clear();
    bonuses.clear();
    balls.push_back(std::make_unique<Ball>(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 100.f), sf::Vector2f(BALL_SPEED / 1.4f, -BALL_SPEED / 1.4f)));
}

void Game::spawnRandomBonus(sf::Vector2f pos) {
    bonuses.push_back(BonusFactory::createRandomBonus(pos));
}

void Game::accelerateActiveBalls() {
    for (auto& ball : balls) { if (ball->isActive()) ball->multiplyVelocity(1.2f); }
}

void Game::processEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

bool Game::checkWinCondition() {
    for (const auto& brick : field->getBricks()) {
        if (brick->isRequiredForWin() && !brick->isDestroyed()) {
            return false;
        }
    }
    return true;
}
void Game::update(float deltaTime) {
    if (isGameOver || isVictory) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) racket->moveLeft(deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) racket->moveRight(deltaTime);

    for (auto& ball : balls) ball->update(deltaTime);
    for (auto& bonus : bonuses) bonus->update(deltaTime);

    CollisionSystem::handleAllCollisions(balls, *racket, *field, bonuses, score, *this);

    if (checkWinCondition()) {
        isVictory = true;
    }

    bool anyAlive = false;
    for (auto& ball : balls) {
        if (ball->isActive()) {
            if (ball->getPosition().y > WINDOW_HEIGHT) ball->deactivate();
            else anyAlive = true;
        }
    }

    if (!anyAlive) {
        lives--;
        if (lives > 0) {
            resetLevel();
        }
        else {
            isGameOver = true;
        }
    }

    std::string title = "Arkanoid | Score: " + std::to_string(score) + " | Lives: " + std::to_string(lives);
    window.setTitle(title);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        RenderSystem::renderGame(window, *field, *racket, balls, bonuses, score, lives, isGameOver, isVictory);
    }
}
Racket& Game::getRacket() { return *racket; }
Field& Game::getField() { return *field; }
void Game::addBall(std::unique_ptr<Ball> ball) { balls.push_back(std::move(ball)); }
