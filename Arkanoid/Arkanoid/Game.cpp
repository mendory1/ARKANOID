#include "Game.h"
#include "Racket.h"
#include "Ball.h"
#include "Field.h"
#include "Bonus.h"
#include "Config.h"
#include "Collision.h"
#include "Functions.h"
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

void Game::processEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

bool Game::checkWinCondition() {
    for (const auto& brick : field->getBricks()) {
        if (!brick->isDestroyed() && brick->getType() != BlockType::Indestructible) {
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

    handleCollisions();

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

void Game::handleCollisions() {
    for (auto& ball : balls) {
        if (!ball->isActive()) continue;

        if (checkCollision(ball->getBounds(), racket->getBounds())) {
            ball->bounceY();
            float hitPoint = (ball->getPosition().x - racket->getPosition().x) / racket->getSize().x;
            ball->setVelocity(sf::Vector2f(BALL_SPEED * 1.5f * (hitPoint - 0.5f), -std::abs(BALL_SPEED / 1.4f)));
        }

        if (field->isExtraBottomActive() && checkCollision(ball->getBounds(), field->getBottomBounds())) {
            ball->bounceY();
            field->deactivateExtraBottom();
        }

        for (auto& brick : field->getBricks()) {
            if (brick->isDestroyed()) continue;

            if (checkCollision(ball->getBounds(), brick->getBounds())) {
                ball->bounceY();
                brick->hit(score);

                if (brick->isDestroyed()) {
                    if (brick->getType() == BlockType::SpeedUp) ball->multiplyVelocity(1.2f);
                    if (brick->getType() == BlockType::WithBonus) {
                        int types[] = { 5, 6, 9 };
                        int chosenType = types[getRandomNumber(0, 2)];
                        bonuses.push_back(std::make_unique<Bonus>(
                            sf::Vector2f(brick->getBounds().position.x + BLOCK_WIDTH / 2, brick->getBounds().position.y),
                            chosenType
                        ));
                    }
                }
                break;
            }
        }
    }

    for (auto& bonus : bonuses) {
        if (bonus->isActive() && checkCollision(bonus->getBounds(), racket->getBounds())) {
            bonus->deactivate();
            if (bonus->getType() == 5) racket->expand();
            else if (bonus->getType() == 6) field->activateExtraBottom();
            else if (bonus->getType() == 9) {
                balls.push_back(std::make_unique<Ball>(sf::Vector2f(racket->getPosition().x + racket->getSize().x / 2.f, racket->getPosition().y - 20.f), sf::Vector2f(-BALL_SPEED / 1.2f, -BALL_SPEED / 1.2f), sf::Color::Red));
            }
        }
    }
}

void Game::drawPixelGameOver() {
    const int pSize = 8;
    sf::RectangleShape pixel({ static_cast<float>(pSize), static_cast<float>(pSize) });
    pixel.setFillColor(sf::Color::Red);

    auto drawChar = [&](const int grid[5][4], float startX, float startY) {
        for (int r = 0; r < 5; ++r) {
            for (int c = 0; c < 4; ++c) {
                if (grid[r][c] == 1) {
                    pixel.setPosition({ startX + c * pSize, startY + r * pSize });
                    window.draw(pixel);
                }
            }
        }
        };

    const int G[5][4] = { {1,1,1,1},{1,0,0,0},{1,0,1,1},{1,0,0,1},{1,1,1,1} };
    const int A[5][4] = { {0,1,1,0},{1,0,0,1},{1,1,1,1},{1,0,0,1},{1,0,0,1} };
    const int M[5][4] = { {1,0,0,1},{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,0,0,1} };
    const int E[5][4] = { {1,1,1,1},{1,0,0,0},{1,1,1,0},{1,0,0,0},{1,1,1,1} };

    const int O[5][4] = { {1,1,1,1},{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1} };
    const int V[5][4] = { {1,0,0,1},{1,0,0,1},{1,0,0,1},{0,1,1,0},{0,1,1,0} };
    const int R[5][4] = { {1,1,1,0},{1,0,0,1},{1,1,1,0},{1,0,1,0},{1,0,0,1} };

    float centerX = WINDOW_WIDTH / 2.f - 80.f;
    float centerY = WINDOW_HEIGHT / 2.f - 40.f;

    drawChar(G, centerX, centerY);
    drawChar(A, centerX + 40, centerY);
    drawChar(M, centerX + 80, centerY);
    drawChar(E, centerX + 120, centerY);

    drawChar(O, centerX, centerY + 50);
    drawChar(V, centerX + 40, centerY + 50);
    drawChar(E, centerX + 80, centerY + 50);
    drawChar(R, centerX + 120, centerY + 50);
}

void Game::drawPixelWin() {
    const int pSize = 10;
    sf::RectangleShape pixel({ static_cast<float>(pSize), static_cast<float>(pSize) });
    pixel.setFillColor(sf::Color::Green);

    auto drawChar = [&](const int grid[5][4], float startX, float startY) {
        for (int r = 0; r < 5; ++r) {
            for (int c = 0; c < 4; ++c) {
                if (grid[r][c] == 1) {
                    pixel.setPosition({ startX + c * pSize, startY + r * pSize });
                    window.draw(pixel);
                }
            }
        }
        };

    const int W[5][4] = { {1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1},{1,0,0,1} };
    const int I[5][4] = { {1,1,1,1},{0,1,1,0},{0,1,1,0},{0,1,1,0},{1,1,1,1} };
    const int N[5][4] = { {1,0,0,1},{1,1,0,1},{1,0,1,1},{1,0,0,1},{1,0,0,1} };

    float centerX = WINDOW_WIDTH / 2.f - 70.f;
    float centerY = WINDOW_HEIGHT / 2.f - 25.f;

    drawChar(W, centerX, centerY);
    drawChar(I, centerX + 55, centerY);
    drawChar(N, centerX + 110, centerY);
}

void Game::render() {
    window.clear(sf::Color::Black);

    float progressBarWidth = std::min(score * 4.f, 200.f);
    if (progressBarWidth > 0) {
        sf::RectangleShape scoreBar({ progressBarWidth, 12.f });
        scoreBar.setFillColor(sf::Color::Green);
        scoreBar.setPosition({ 15.f, 15.f });
        window.draw(scoreBar);
    }

    sf::RectangleShape scoreBorder({ 200.f, 12.f });
    scoreBorder.setFillColor(sf::Color::Transparent);
    scoreBorder.setOutlineColor(sf::Color(100, 100, 100));
    scoreBorder.setOutlineThickness(1.f);
    scoreBorder.setPosition({ 15.f, 15.f });
    window.draw(scoreBorder);

    for (int i = 0; i < lives; ++i) {
        sf::RectangleShape lifeIcon({ 30.f, 8.f });
        lifeIcon.setFillColor(sf::Color::White);
        lifeIcon.setPosition({ WINDOW_WIDTH - 45.f - (i * 40.f), 17.f });
        window.draw(lifeIcon);
    }

    sf::RectangleShape separator({ static_cast<float>(WINDOW_WIDTH), 2.f });
    separator.setFillColor(sf::Color(50, 50, 50));
    separator.setPosition({ 0.f, 40.f });
    window.draw(separator);

    field->draw(window);
    racket->draw(window);
    for (auto& ball : balls) ball->draw(window);
    for (auto& bonus : bonuses) bonus->draw(window);

    if (isGameOver || isVictory) {
        sf::RectangleShape fadeOverlay({ static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT) });
        fadeOverlay.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(fadeOverlay);

        if (isGameOver) {
            drawPixelGameOver();
        }
        else if (isVictory) {
            drawPixelWin();
        }
    }

    window.display();
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}
