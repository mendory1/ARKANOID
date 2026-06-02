#pragma once
#include <SFML/Graphics.hpp>

inline bool checkCollision(const sf::FloatRect& a, const sf::FloatRect& b) {
    return a.findIntersection(b).has_value();
}
