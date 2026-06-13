#include "RenderSystem.h"
#include "Field.h"
#include "Racket.h"
#include "Ball.h"
#include "Bonus.h"
#include "Config.h"
#include <algorithm>

void RenderSystem::renderGame(
    sf::RenderWindow& window,
    Field& field,
    Racket& racket,
    const std::vector<std::unique_ptr<Ball>>& balls,
    const std::vector<std::unique_ptr<Bonus>>& bonuses,
    int score,
    int lives,
    bool isGameOver,
    bool isVictory)
{
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

    field.draw(window);
    racket.draw(window);
    for (auto& ball : balls) ball->draw(window);
    for (auto& bonus : bonuses) bonus->draw(window);

    if (isGameOver || isVictory) {
        sf::RectangleShape fadeOverlay({ static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT) });
        fadeOverlay.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(fadeOverlay);
        if (isGameOver) drawPixelGameOver(window);
        else drawPixelWin(window);
    }

    window.display();
}

void RenderSystem::drawPixelGameOver(sf::RenderWindow& window) {
    const int pSize = 8;
    sf::RectangleShape pixel({ static_cast<float>(pSize), static_cast<float>(pSize) });
    pixel.setFillColor(sf::Color::Red);

    auto drawChar = [&](const std::vector<std::vector<int>>& grid, float startX, float startY) {
        for (int r = 0; r < 5; ++r) {
            for (int c = 0; c < 4; ++c) {
                if (grid[r][c] == 1) {
                    pixel.setPosition({ startX + c * pSize, startY + r * pSize });
                    window.draw(pixel);
                }
            }
        }
        };

    std::vector<std::vector<int>> G = { {1,1,1,1},{1,0,0,0},{1,0,1,1},{1,0,0,1},{1,1,1,1} };
    std::vector<std::vector<int>> A = { {0,1,1,0},{1,0,0,1},{1,1,1,1},{1,0,0,1},{1,0,0,1} };
    std::vector<std::vector<int>> M = { {1,0,0,1},{1,1,1,1},{1,0,0,1},{1,0,0,1},{1,0,0,1} };
    std::vector<std::vector<int>> E = { {1,1,1,1},{1,0,0,0},{1,1,1,0},{1,0,0,0},{1,1,1,1} };
    std::vector<std::vector<int>> O = { {1,1,1,1},{1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1} };
    std::vector<std::vector<int>> V = { {1,0,0,1},{1,0,0,1},{1,0,0,1},{0,1,1,0},{0,1,1,0} };
    std::vector<std::vector<int>> R = { {1,1,1,0},{1,0,0,1},{1,1,1,0},{1,0,1,0},{1,0,0,1} };

    float centerX = WINDOW_WIDTH / 2.f - 80.f;
    float centerY = WINDOW_HEIGHT / 2.f - 40.f;

    drawChar(G, centerX, centerY); drawChar(A, centerX + 40, centerY);
    drawChar(M, centerX + 80, centerY); drawChar(E, centerX + 120, centerY);
    drawChar(O, centerX, centerY + 50); drawChar(V, centerX + 40, centerY + 50);
    drawChar(E, centerX + 80, centerY + 50); drawChar(R, centerX + 120, centerY + 50);
}

void RenderSystem::drawPixelWin(sf::RenderWindow& window) {
    const int pSize = 10;
    sf::RectangleShape pixel({ static_cast<float>(pSize), static_cast<float>(pSize) });
    pixel.setFillColor(sf::Color::Green);

    auto drawChar = [&](const std::vector<std::vector<int>>& grid, float startX, float startY) {
        for (int r = 0; r < 5; ++r) {
            for (int c = 0; c < 4; ++c) {
                if (grid[r][c] == 1) {
                    pixel.setPosition({ startX + c * pSize, startY + r * pSize });
                    window.draw(pixel);
                }
            }
        }
        };

    std::vector<std::vector<int>> W = { {1,0,0,1},{1,0,0,1},{1,0,0,1},{1,1,1,1},{1,0,0,1} };
    std::vector<std::vector<int>> I = { {1,1,1,1},{0,1,1,0},{0,1,1,0},{0,1,1,0},{1,1,1,1} };
    std::vector<std::vector<int>> N = { {1,0,0,1},{1,1,0,1},{1,0,1,1},{1,0,0,1},{1,0,0,1} };

    float centerX = WINDOW_WIDTH / 2.f - 70.f;
    float centerY = WINDOW_HEIGHT / 2.f - 25.f;

    drawChar(W, centerX, centerY); drawChar(I, centerX + 55, centerY); drawChar(N, centerX + 110, centerY);
}
