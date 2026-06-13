#include "BonusBall.h"
#include "Game.h"
#include "Ball.h"
#include "Racket.h"
#include "Config.h"

BonusBall::BonusBall(sf::Vector2f pos) : Bonus(pos, sf::Color::Cyan) {}
void BonusBall::activateEffect(Game& game) {
    game.addBall(std::make_unique<Ball>(
        sf::Vector2f(game.getRacket().getPosition().x + game.getRacket().getSize().x / 2.f, game.getRacket().getPosition().y - 20.f),
        sf::Vector2f(-BALL_SPEED / 1.2f, -BALL_SPEED / 1.2f),
        sf::Color::Red
    ));
}
