#include "Ball.h"
#include "Config.h"

Ball::Ball(sf::Vector2f startPos, sf::Vector2f startVel, sf::Color color) {
    shape.setRadius(BALL_RADIUS);
    shape.setFillColor(color);
    shape.setOrigin({ BALL_RADIUS, BALL_RADIUS });
    shape.setPosition(startPos);
    velocity = startVel;
    active = true;
}
void Ball::update(float deltaTime) {
    if (!active) return;
    shape.move(velocity * deltaTime);

    if (shape.getPosition().x - BALL_RADIUS < 0) {
        shape.setPosition({ BALL_RADIUS, shape.getPosition().y });
        bounceX();
    }
    else if (shape.getPosition().x + BALL_RADIUS > WINDOW_WIDTH) {
        shape.setPosition({ WINDOW_WIDTH - BALL_RADIUS, shape.getPosition().y });
        bounceX();
    }
    if (shape.getPosition().y - BALL_RADIUS < 0) {
        shape.setPosition({ shape.getPosition().x, BALL_RADIUS });
        bounceY();
    }
}
void Ball::draw(sf::RenderWindow& window) { if (active) window.draw(shape); }
sf::FloatRect Ball::getBounds() const { return shape.getGlobalBounds(); }
