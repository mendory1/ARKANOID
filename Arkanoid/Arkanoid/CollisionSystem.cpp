#include "CollisionSystem.h"
#include "Ball.h"
#include "Racket.h"
#include "Field.h"
#include "Bonus.h"
#include "Brick.h"
#include "Collision.h"
#include "Config.h"
#include <cmath>

void CollisionSystem::handleAllCollisions(
    std::vector<std::unique_ptr<Ball>>& balls,
    Racket& racket,
    Field& field,
    std::vector<std::unique_ptr<Bonus>>& bonuses,
    int& score,
    Game& game)
{
    for (auto& ball : balls) {
        if (!ball->isActive()) continue;

        if (checkCollision(ball->getBounds(), racket.getBounds())) {
            ball->bounceY();
            float hitPoint = (ball->getPosition().x - racket.getPosition().x) / racket.getSize().x;
            ball->setVelocity(sf::Vector2f(BALL_SPEED * 1.5f * (hitPoint - 0.5f), -std::abs(BALL_SPEED / 1.4f)));
        }

        if (field.isExtraBottomActive() && checkCollision(ball->getBounds(), field.getBottomBounds())) {
            ball->bounceY();
            field.deactivateExtraBottom();
        }

        for (auto& brick : field.getBricks()) {
            if (brick->isDestroyed()) continue;
            if (checkCollision(ball->getBounds(), brick->getBounds())) {
                ball->bounceY();
                brick->hit(score, game);
                break;
            }
        }
    }

    for (auto& bonus : bonuses) {
        if (bonus->isActive() && checkCollision(bonus->getBounds(), racket.getBounds())) {
            bonus->deactivate();
            bonus->activateEffect(game);
        }
    }
}
