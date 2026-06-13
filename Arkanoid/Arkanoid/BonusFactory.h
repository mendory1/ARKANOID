#pragma once
#include <memory>
#include <SFML/System/Vector2.hpp>

class Bonus;

class BonusFactory {
public:
    static std::unique_ptr<Bonus> createRandomBonus(sf::Vector2f pos);
};
