#include "Collision.h"
#include "Racket.h"
#include "Ball.h"
#include "Field.h"
#include "Brick.h"
#include "Bonus.h"
#include "Game.h"
#include "Config.h"
#include <cmath>

void handleAllCollisions(Racket& racket, std::vector<std::unique_ptr<Ball>>& balls, Field& field, std::vector<std::unique_ptr<Bonus>>& bonuses, int& score, Game& game) {
    auto checkIntersection = [](const sf::FloatRect& a, const sf::FloatRect& b) {
        return a.findIntersection(b).has_value();
        };

    for (auto& ball : balls) {
        if (!ball->isActive()) continue;

        if (checkIntersection(ball->getBounds(), racket.getBounds())) {
            ball->bounceY();
            float hitPoint = (ball->getPosition().x - racket.getPosition().x) / racket.getSize().x;
            ball->setVelocity(sf::Vector2f(BALL_SPEED * 1.5f * (hitPoint - 0.5f), -std::abs(BALL_SPEED / 1.4f)));
        }

        if (field.isExtraBottomActive() && checkIntersection(ball->getBounds(), field.getBottomBounds())) {
            ball->bounceY();
            field.deactivateExtraBottom();
        }

        for (auto& brick : field.getBricks()) {
            if (brick->isDestroyed()) continue;
            if (checkIntersection(ball->getBounds(), brick->getBounds())) {
                ball->bounceY();
                brick->hit(score, game);
                break;
            }
        }
    }

    for (auto& bonus : bonuses) {
        if (bonus->isActive() && checkIntersection(bonus->getBounds(), racket.getBounds())) {
            bonus->deactivate();
            bonus->activateEffect(game);
        }
    }
}
